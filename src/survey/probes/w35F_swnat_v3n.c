/* w35F (unnamed) @ 0x24e6a, 46 B — v3n: naked-asm escape (CL /O2 pushes the
 * two repeated constant args as 68-imm32 (48 B); FA holds them in esi/edi
 * regs and pushes regs = 46 B. No C spelling survives CL's const-prop, so
 * naked-asm reproduces FA verbatim. Calls: _Swapmem@12 x2 (rel @0x14, @0x26),
 * ?MenuCreateRemaps@@YGXXZ (rel @0x19); abs: _nationSides+0x58 (@0x2, @0x20),
 * _curPalette (@0xe). 46 B, no tail. */
extern char nationSides[];   /* bare public _nationSides */
extern char curPalette[];    /* bare public _curPalette */
extern void __cdecl w35f_swapmem(long, void *, long);  /* -> _Swapmem@12 */
extern void __cdecl w35f_mcr(void);                    /* -> ?MenuCreateRemaps@@YGXXZ */

void __declspec(naked) __cdecl w35f_swnat(void)
{
    __asm {
        push esi
        mov eax, dword ptr [nationSides+0x58]
        push edi
        mov esi, 300h
        push esi
        mov edi, offset curPalette
        push edi
        push eax
        call w35f_swapmem
        call w35f_mcr
        push esi
        mov eax, dword ptr [nationSides+0x58]
        push edi
        push eax
        call w35f_swapmem
        pop edi
        pop esi
        ret
    }
}