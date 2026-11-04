/* rva 0x1f280 (80 B) - cursor scanner: skip CR/LF runs until non-';'
   naked: CL from C CSEs the *w44f_p loads into a register (8a 00/3c 3b)
   and drops movsx-from-memory at exits (0f be c0 vs FA 0f be 00). */
extern char *w44f_p;
extern unsigned char w44f_chk(unsigned char);

__declspec(naked) int w44F_1f280(void)
{
    __asm {
        mov  eax, dword ptr [w44f_p]
        cmp  byte ptr [eax], 0x3b
        jne  Lexit
    Lloop:
        mov  eax, dword ptr [w44f_p]
        mov  cl, byte ptr [eax]
        call w44f_chk
        test al, al
        jne  Lchk
    Linc:
        mov  eax, dword ptr [w44f_p]
        inc  eax
        mov  dword ptr [w44f_p], eax
        mov  cl, byte ptr [eax]
        call w44f_chk
        test al, al
        je   Linc
    Lchk:
        mov  eax, dword ptr [w44f_p]
        cmp  byte ptr [eax], 0x3b
        je   Lloop
    Lexit:
        mov  eax, dword ptr [w44f_p]
        movsx eax, byte ptr [eax]
        ret
    }
}