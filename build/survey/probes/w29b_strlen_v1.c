// w29b E: _strlen @ rva 0xd5ab0 (123 B, no tail pad). FA's body is the CRT
// x86 strlen asm (0x7efefeff word loop, movzx-free byte checks, lea+reload
// +sub returns with the base pulled from [esp+4] each time, and a census
// filler `add eax,0` inside the alignment loop) — not C-formable; naked asm
// with FA's own instruction sequence verbatim.
void __declspec(naked) strlen_q(const char *str)
{
    __asm {
        mov ecx, [esp+4]
        test ecx, 3
        je Laligned
    Lb1:
        mov al, [ecx]
        inc ecx
        test al, al
        je Lr1
        test ecx, 3
        jne Lb1
        add eax, 0
    Laligned:
        mov eax, [ecx]
        mov edx, 07efefeffh
        add edx, eax
        xor eax, -1
        xor eax, edx
        add ecx, 4
        test eax, 081010100h
        je Laligned
        mov eax, [ecx-4]
        test al, al
        je Lr4
        test ah, ah
        je Lr3
        test eax, 0ff0000h
        je Lr2
        test eax, 0ff000000h
        je Lr1
        jmp Laligned
    Lr1:
        lea eax, [ecx-1]
        mov ecx, [esp+4]
        sub eax, ecx
        ret
    Lr4:
        lea eax, [ecx-4]
        mov ecx, [esp+4]
        sub eax, ecx
        ret
    Lr2:
        lea eax, [ecx-2]
        mov ecx, [esp+4]
        sub eax, ecx
        ret
    Lr3:
        lea eax, [ecx-3]
        mov ecx, [esp+4]
        sub eax, ecx
        ret
    }
}