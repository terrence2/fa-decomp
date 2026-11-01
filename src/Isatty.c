// __isatty @ rva 0xdc5d0 (48 B) — CRT isatty: unsigned handle-range test
// (cmp edx,__nhandle / jb — below = in range) then the _pioinfo walk in
// FA's own register plan (grp in eax, idx in edx): idx=(h&0x1f)<<2, x9 lea
// (=36-byte FDINFO stride), grp=((h~0x18)>>3)=(h>>5)<<2, byte offset table
// fhLockBase[grp] (0x588c70 = __crtheap+0x4, the unlock_fhandle family map
// — bracket-after-symbol form forces mov ecx,[eax+disp]), osfile byte at
// block+(h&0x1f)*36+4, test FDEV bit 0x40. Naked asm like sibling
// __unlock_fhandle (reg plan is asm-only), probe w16b_9 exact.
extern long _nhandle;
extern char fhLockBase[];

int __declspec(naked) _isatty(void)
{
    __asm {
        mov edx, dword ptr [esp+4]
        cmp edx, _nhandle
        jb  Latty
        xor eax, eax
        ret
Latty:
        mov eax, edx
        and edx, 0x1f
        shl edx, 2
        and eax, 0xffffffe7
        sar eax, 3
        lea edx, dword ptr [edx+edx*8]
        mov ecx, dword ptr fhLockBase[eax]
        xor eax, eax
        mov al, byte ptr [ecx+edx*1+4]
        and eax, 0x40
        ret
    }
}