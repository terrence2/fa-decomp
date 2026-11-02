// 0x986e0 — v5: naked asm (FA store order is load-bearing; CL hoists)
extern char w28c_mpArr[];
extern char w28c_ctrlArr[];

void __declspec(naked) __cdecl w28c_serShutLL(void)
{
    __asm {
        xor edx, edx
        mov eax, [w28c_mpArr + 0x154]
        cmp eax, edx
        je L1
        mov eax, 1
        mov cl, [w28c_mpArr + 0x164]
        shl eax, cl
        mov byte ptr [w28c_ctrlArr + 0x12d], dl
        mov [w28c_mpArr + 0x158], eax
        mov [w28c_mpArr + 0x160], edx
    L1:
        ret
    }
}
