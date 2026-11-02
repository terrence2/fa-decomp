// 0x986e0 ?SER_ShutdownLowLevel@@YAXXZ @ 0x4986e0 — v7: naked asm over
// per-site extern anchors (MAP-ADDEND in final config: anchor+0x154 etc.)
// moffs A-form (a1/a3) and 89 15/8a 0d/88 15 d-forms, exact per FA decode
extern long w28c_m154, w28c_m158, w28c_m160;
extern char w28c_m164, w28c_c12d;

void __declspec(naked) __cdecl w28c_serShutLL(void)
{
    __asm {
        xor edx, edx
        mov eax, w28c_m154
        cmp eax, edx
        je L1
        mov eax, 1
        mov cl, w28c_m164
        shl eax, cl
        mov w28c_c12d, dl
        mov w28c_m158, eax
        mov w28c_m160, edx
L1:
        ret
    }
}