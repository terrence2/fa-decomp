// @G_StringHeight@0 @ rva 0x96b50 (16 B) — mov eax,[?cFont@@3PAUFONT@@A] /
//   mov eax,[eax] / ret — the first dword of the current FONT is the height.
// (array-typed extern keeps CL's second deref on eax; a scalar decl makes CL
// route it through ecx: a1 / 8b08 / 8b01 — different 4 bytes)
extern void *cFont_x[];

void * __fastcall G_StringHeight(void)
{
    return *(void **)*(void **)cFont_x;
}