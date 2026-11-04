/* FormatField @ rva 0xc2e34 (88 B) -- w45B v1. Naked-asm transcription.
 * ABI: edi is the register param (caller _Sprintf holds the write cursor in
 * edi across the call; FormatField advances it and returns it in edi) -- the
 * sibling call sites at 0x4c2c8e..0x4c2d46 all call straight off the edi
 * cursor. Body: count/limit checks against _curThingType+0x33c/+0x344, then
 * std/rep movsb right-shift of the tail, cld, rep stosb fill with the byte
 * at +0x348. Interior-data refs via map-renamed extern anchors (w42E
 * interior-data recipe): FROM _w45b_ct33x TO _curThingType+0x33x. */
extern unsigned long w45b_ct33c;
extern unsigned long w45b_ct340;
extern unsigned long w45b_ct344;
extern unsigned char w45b_ct348;

void __declspec(naked) FormatField(void)
{
    __asm {
        cmp  w45b_ct33c, -1
        je   w45bff_end
        cmp  edi, w45b_ct344
        jbe  w45bff_shift
        mov  edi, w45b_ct344
        inc  edi
        ret
w45bff_shift:
        mov  ecx, w45b_ct344
        sub  ecx, edi
        inc  ecx
        je   w45bff_end
        push esi
        push edi
        mov  ebx, ecx
        std
        mov  ecx, edi
        sub  ecx, w45b_ct340
        mov  esi, edi
        dec  esi
        mov  edi, w45b_ct344
        rep  movsb
        cld
        mov  ecx, ebx
        pop  edi
        pop  esi
        mov  al, w45b_ct348
        mov  edi, w45b_ct340
        rep  stosb
        mov  edi, w45b_ct344
        inc  edi
w45bff_end:
        ret
    }
}