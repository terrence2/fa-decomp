/* Remap @ rva 0xc87fc (104 B) -- w45B v1. Naked-asm transcription. eax=color,
 * ebx=flags mask. Effects-gated palette pass chain: shade (bit 8 of _effects),
 * two-lamp palette remap (bit 0x10, _realPalette+0x304/+0x308), tint, then
 * _globalColorAdd unless eax==0xff. High path (jge 0x100): movzx table
 * walk [_tempYLR+0x4c78][eax*2], loop back on eax<0x100 (banded table).
 * 16-bit test of _effects (66 f7 /0 iw). Scaled load uses anchor map with
 * sym[index*2] spelling (CL drops [reg+sym] bases). Tail filler 8b c0. */
extern unsigned short effects;               /* _effects */
extern unsigned long currentShadeTable[];    /* _currentShadeTable */
extern unsigned long realPalette[];          /* _realPalette (+0x304/+0x308) */
extern unsigned long currentTintTable[];     /* _currentTintTable */
extern unsigned long globalColorAdd;         /* _globalColorAdd */
extern unsigned long w45b_tyl;               /* emits _w45b_tyl */

void __declspec(naked) Remap_45b(void)
{
    __asm {
        push ecx
        cmp  eax, 0x100
        jge  w45brm_hi
w45brm_test:
        test word ptr effects, 8
        je   w45brm_pop
        mov  ecx, currentShadeTable
        or   ebx, ebx
        je   w45brm_t2
        mov  al, byte ptr [eax+ecx]
w45brm_t2:
        test word ptr effects, 0x10
        je   w45brm_tint
        mov  ebx, dword ptr realPalette[0x304]
        mov  ecx, dword ptr realPalette[0x308]
        mov  al, byte ptr [eax+ebx]
        mov  al, byte ptr [eax+ecx]
w45brm_tint:
        mov  ebx, currentTintTable
        mov  al, byte ptr [eax+ebx]
        cmp  eax, 0xff
        je   w45brm_pop
        add  eax, globalColorAdd
w45brm_pop:
        pop  ecx
        ret
w45brm_hi:
        movzx eax, word ptr w45b_tyl[eax*2]
        cmp  eax, 0x100
        jl   w45brm_test
        pop  ecx
        ret
    }
}