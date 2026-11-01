// _GetFakeKey@0 @ rva 0x11cb0 (48 B) — word counter at _waitCounter+4:
// mov ax/test/je, in-reg 16-bit dec (66 48) + moffs store-back, movsx'd
// index, word table read adCount+8[ecx*2], ret; zero path xor ax,ax/ret.
// Return value lives in AX (ushort-return shape); 66-regs are asm-only.
extern char waitCounter[];
extern char adCount[];          // ?adCount@@3EA

__declspec(naked) void __stdcall GetFakeKey_q(void)
{
    __asm {
        mov ax, word ptr [waitCounter+4]
        test ax, ax
        je fin
        dec ax
        mov word ptr [waitCounter+4], ax
        movsx ecx, ax
        mov ax, word ptr [adCount + ecx*2 + 8]
        ret
    fin:
        xor ax, ax
        ret
    }
}