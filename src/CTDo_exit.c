extern char serviceTicks[];
extern void __fastcall ctdoQuit_(int a);
__declspec(naked) void CTDo_exit(void)
{
    __asm {
        mov al, byte ptr [serviceTicks + 0xec]
        test al, al
        jnz fin
        xor ecx, ecx
        call ctdoQuit_
        mov cl, byte ptr [serviceTicks + 0xf8]
        or cl, al
        mov byte ptr [serviceTicks + 0xf8], cl
        fin: ret
    }
}
