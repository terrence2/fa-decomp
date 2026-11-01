// @G_SetFont@4 @ rva 0x967d0 (8 B) — mov [?cFont@@3PAUFONT@@A],ecx / ret —
//   store the fastcall arg into the current-font pointer.
extern void *cFont_x;

void __fastcall G_SetFont(void *f)
{
    cFont_x = f;
}