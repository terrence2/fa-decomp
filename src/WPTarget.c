// _WPTarget@4 @ rva 0x97ad0 — unaligned dword read at +0x21 of the waypointer,
// 16-bit returns (xor ax,ax / mov ax,cx) and a relink escape for negative ids;
// 16-bit reg forms are CL-unreachable in C — naked asm (probe w11b_02, byte-exact)
extern unsigned short __stdcall wpRelink_(void);
__declspec(naked) unsigned short __stdcall WPTarget_q(int p)
{
    __asm {
        mov eax, [esp+4]
        mov ecx, [eax+0x21]
        test ecx, ecx
        jnz L1
        xor ax, ax
        ret 4
    L1:
        test ecx, 0x80000000
        jz L2
        call wpRelink_
        ret 4
    L2:
        mov ax, cx
        ret 4
    }
}