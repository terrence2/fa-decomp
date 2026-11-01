// @ButtonSound@4 @ rva 0x12820 — button beep: name pointer picked by the flag
// byte (default 0x4e8e78, flag==0 -> 0x4e8e68) interleaved with the SingleSound
// argument pushes; CL's C scheduler cannot interleave like that — naked asm
// (probe w11b_10, byte-exact)
extern short __stdcall SingleSoundS(char *a, short b, unsigned char c, short d);
extern char btnSndLo[];   // -> ?doReceiveInGetKey@@3DA+0x5c  (0x4e8e68)
extern char btnSndHi[];   // -> ?doReceiveInGetKey@@3DA+0x6c  (0x4e8e78)
__declspec(naked) void __fastcall ButtonSound_q(void)
{
    __asm {
        push 0
        mov eax, offset btnSndHi
        push 0ffh
        test cl, cl
        push 080h
        jne fin
        mov eax, offset btnSndLo
    fin:
        push eax
        call SingleSoundS
        ret
    }
}