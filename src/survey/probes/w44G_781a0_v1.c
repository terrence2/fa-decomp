// w44G @ 0x4781a0 (rva 0x781a0, 128 B) _LibShutDown: void cdecl(void).
// Shuts ?hintHndl@@3PAUT_HANDLE@@A: zero hint flag a0/88 1d pair, free
// each libHandle slot via @MMFreeHandle@4 (fastcall, arg in ecx — no
// push!), rep stosd the 0x14-dword libHandle band, free hintHndl, call
// @MMCompactRAM@0, then 4 accumulator stores (a3) INTERLEAVED with the
// pops (5f 5e a3 ... 5b a3 ...). Interleaved stores + a3 moffs forms =
// naked whole-body transcription. DIR32 sites 02/15/1b/24/34/41/50/63/69/6e/73.
extern unsigned char w44G_hh[];      /* ?hintHndl@@3PAUT_HANDLE@@A @0x4f3f24 */
extern unsigned char w44G_nh[];      /* ?numHandles@@3JA @0x545ec0 */
extern unsigned char w44G_lh[];      /* ?libHandle@@3PAPAUT_HANDLE@@A @0x545e70 */
extern unsigned char w44G_ni[];      /* ?numHints@@3JA @0x542c18 */
extern unsigned char w44G_nfh[];     /* ?numFreeHints@@3JA @0x542c1c */
extern void __fastcall MMFreeHandle(void *h);
extern char __fastcall MMCompactRAM(void);
__declspec(naked) void _LibShutDown(long a)
{
    __asm {
        push ebx
        mov al, BYTE PTR w44G_hh[4]
        push esi
        test al, al
        push edi
        jnz L1
        xor eax, eax
        pop edi
        pop esi
        pop ebx
        ret
    L1:
        xor ebx, ebx
        mov eax, DWORD PTR w44G_nh
        mov BYTE PTR w44G_hh[4], bl
        cmp eax, ebx
        jle Lz
        mov esi, OFFSET w44G_lh
    Lloop:
        mov ecx, DWORD PTR [esi]
        test ecx, ecx
        je Ls
        call MMFreeHandle
        mov eax, DWORD PTR w44G_nh
    Ls:
        add esi, 4
        inc ebx
        cmp eax, ebx
        jg Lloop
    Lz:
        mov edi, OFFSET w44G_lh
        xor eax, eax
        mov ecx, 0x14
        rep stosd
        mov ecx, DWORD PTR w44G_hh
        call MMFreeHandle
        call MMCompactRAM
        xor eax, eax
        pop edi
        pop esi
        mov DWORD PTR w44G_hh, eax
        pop ebx
        mov DWORD PTR w44G_ni, eax
        mov DWORD PTR w44G_nfh, eax
        mov DWORD PTR w44G_nh, eax
        ret
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00
    }
}