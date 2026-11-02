// _RMShutdown@0 @ rva 0xa36c0 (61 B code + 3 B 8d49 pad) — walks a 0x13
// -stride array from ?resList@@3PAURES_LIST@@A, RMFree()ing each nonempty
// entry head, then f3 ab-rep stosd zeroes 0x19fa dwords and clears the
// trailing allocated-flag byte at +0x67e8.  The immediates 0x4ff720 /
// 0x505f08 carry DIR32 relocs to the resList symbol (human-coin +0x0 /
// +0x67e8 maps) — MASM offset forms; a0/a2 moffs for the flag byte.
extern char resListArr[];               /* ?resList@@3PAURES_LIST@@A */
extern char resEnd;                     /* ?resList@@3PAURES_LIST@@A+0x67e8 */
extern void __stdcall RMFree(char* p);

__declspec(naked) void __stdcall RMShutdown_q(void)
{
    __asm {
        push esi
        mov  al, byte ptr resEnd
        push edi
        test al, al
        je   Ldone
        mov  esi, offset resListArr
    Llp:mov  al, byte ptr [esi]
        test al, al
        je   Lskip
        push esi
        call RMFree
    Lskip:
        add  esi, 13h
        cmp  esi, offset resEnd
        jb   Llp
        mov  edi, offset resListArr
        xor  eax, eax
        mov  ecx, 019fah
        rep  stosd
        mov  resEnd, al
    Ldone:
        pop  edi
        pop  esi
        ret
    }
}