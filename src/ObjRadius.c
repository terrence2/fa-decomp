// @ObjRadius@4 @ rva 0x127a0 — test ecx,ecx / jz shared-tail / mov ecx,
//   [ecx+0xf] / test ecx,ecx / jz shared-tail / movsx eax,word [ecx+4] /
//   mov cl,[ecx+6] / shl eax,cl / ret; shared tail xor eax,eax / ret.
//   Single-exit nested if — the two-return form gives inverted jz shapes
//   (probe v4 wrong, w4_objrad.obj exact).
int __fastcall ObjRadius(void *o)
{
    if (o) {
        o = *(void **)((char *)o + 0xf);
        if (o)
            return *(short *)((char *)o + 4)
                   << *(unsigned char *)((char *)o + 6);
    }
    return 0;
}
