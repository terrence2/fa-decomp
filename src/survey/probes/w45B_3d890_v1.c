/* ?UsingSuppRadar@@YADXZ @ rva 0x3d890 (128 B, tail pads 8d642400 x2) --
 * w45B v1. Naked-asm transcription. Returns AL=1 iff the support-radar obj
 * is currently rendering as viewed: gates on ?onSuppRadar@@3DA byte, then
 * ch-bit 0x40 (ch = byte 1 of [obj->5+0xba]) with _curThing+0xde flag test
 * a9 0x104000 and range check ([objSuppRadar->0x15] & 0xffffff00 vs 0x3e800,
 * jle = must exceed), or ch-bit 0x20 path with the _currentT/_curThing+0x11a
 * 16-bit compare and ah 0x20 test, same range check. Anchor maps for the
 * interior _curThing+0x11a/+0xde moffs; real publics onSuppRadar/objSuppRadar
 * via bare C spellings. */
extern unsigned char onSuppRadar;            /* _onSuppRadar */
extern unsigned long objSuppRadar;           /* _objSuppRadar */
extern unsigned long w45b_ctde;              /* emits _w45b_ctde */
extern unsigned short w45b_ct11a;            /* emits _w45b_ct11a */
extern unsigned short currentT;              /* _currentT */

char __declspec(naked) UsingSuppRadar_45b(void)
{
    __asm {
        mov  al, onSuppRadar
        test al, al
        je   w45bsr_no
        mov  eax, objSuppRadar
        mov  edx, [eax+5]
        mov  ecx, [edx+0xba]
        test ch, 0x40
        je   w45bsr_p2
        mov  eax, w45b_ctde
        test eax, 0x104000
        je   w45bsr_p2
        mov  eax, objSuppRadar
        mov  eax, [eax+0x15]
        and  eax, 0xffffff00
        cmp  eax, 0x3e800
        jle  w45bsr_p2
        mov  al, 1
        ret
w45bsr_p2:
        test ch, 0x20
        je   w45bsr_no
        mov  cx, currentT
        cmp  w45b_ct11a, cx
        ja   w45bsr_hi
        mov  eax, w45b_ctde
        test ah, 0x20
        je   w45bsr_no
w45bsr_hi:
        mov  eax, objSuppRadar
        mov  eax, [eax+0x15]
        and  eax, 0xffffff00
        cmp  eax, 0x3e800
        jle  w45bsr_no
        mov  al, 1
        ret
w45bsr_no:
        xor  al, al
        ret
    }
}