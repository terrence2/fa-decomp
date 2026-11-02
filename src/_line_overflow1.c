// _line_overflow1 @ rva 0xbb660 (80 B, FPO fpo/esp params=1) — SEH
// exception filter for the integer line-overflow site: reads
// ExceptionCode (**ep) and matches C0000094 (integer div-by-zero) /
// C0000095 (integer overflow); both je's land IN the handler body
// (0x4bb679), which swaps the two dwords at +0x9c/+0xa4 of the exception
// context record pointee ([ecx+4]) — the classic FA swap-pair — and
// stores the restart address _line_overflow_goes_here at +0xb8 (c7 80
// mem-imm, DIS elided in dis.py — symbol via map, literal-VA trap rule)
// then returns -1 (EXCEPTION_EXECUTE_HANDLER); 0 otherwise. Naked asm:
// FA streams eax-first cmp 3d imm32 pairs without reloads (CL would
// re-load *er per compare).
extern void *lineOverflowHere;

int __declspec(naked) line_overflow1(void)
{
    __asm {
        mov  ecx, dword ptr [esp+4]
        mov  eax, dword ptr [ecx]
        mov  eax, dword ptr [eax]
        cmp  eax, 0xc0000094
        je   Lhit
        cmp  eax, 0xc0000095
        je   Lhit
        xor  eax, eax
        ret
    Lhit:
        mov  eax, dword ptr [ecx+4]
        mov  ecx, dword ptr [eax+0xa4]
        mov  edx, dword ptr [eax+0x9c]
        mov  dword ptr [eax+0xa4], edx
        mov  dword ptr [eax+0x9c], ecx
        mov  dword ptr [eax+0xb8], offset lineOverflowHere
        mov  eax, -1
        ret
    }
}