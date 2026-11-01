// _wcslen @ rva 0xe0be0 (24 B) — the CRT loop: mov ecx,[esp+4] / mov eax,ecx
//   / mov edx,eax / add eax,2 / cmp word [edx],0 / jne / sub eax,ecx /
//   sar eax,1 / dec eax / ret. CL's C version emits the element-conversion
//   or a 1-byte sar, never FA's c1-immediate form (probes d25/d28/d31/d34),
//   so the leaf is inline __asm with a backward label (no relocs).
void Wcslen_q(void)
{
    __asm {
        mov     ecx, dword ptr [esp+4]
        mov     eax, ecx
wcs_loop:
        mov     edx, eax
        add     eax, 2
        cmp     word ptr [edx], 0
        jne     wcs_loop
        sub     eax, ecx
        // MASM normalises sar eax,1 to the 1-byte d1 form; FA carries the
        // c1-immediate encoding, so the shift is emitted by hand.
        _emit   0xC1
        _emit   0xF8
        _emit   0x01
        dec     eax
    }
}
