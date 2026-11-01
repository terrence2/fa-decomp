// @G_SetBitmap@4 @ rva 0x95610 (8 B) — mov [_cb],ecx / ret — store the
//   fastcall arg into the graphics-block pointer _cb.
extern void *cb;

void __fastcall G_SetBitmap(void *b)
{
    cb = b;
}