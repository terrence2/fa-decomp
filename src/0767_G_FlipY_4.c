// @G_FlipY@4 @ rva 0x95460 (16 B) — mov eax,[_cb] / mov eax,[eax+6] /
//   sub eax,ecx / dec eax / ret — mirror-flip of a Y coordinate inside the
//   block pointed to by _cb.
extern long cb[];

int __fastcall G_FlipY(int a)
{
    return *(long *)((char *)*(long *)cb + 6) - a - 1;
}