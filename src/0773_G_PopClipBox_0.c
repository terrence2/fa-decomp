// @G_PopClipBox@0 @ rva 0x95780 (48 B) — FA asm: a1 [_globalSecondarySurface+0x4]
// / dec eax / a3 store-back / movsx edx,word [eax*8+0x4e26] (popTb elem 3) /
// lea ecx,[eax*8+0x4e20] / push edx / movsx eax,[ecx+4] / movsx edx,[ecx+2] /
// movsx ecx,[ecx] / push eax / call @G_SetClipBox@16 / ret.
// asm escape (probe b17c_gpopclipbox_v2 byte-exact): plain C scheduled
// differently — an extra mov ecx,eax, the movsxs as 4 separate sib+disp sites
// instead of the lea-baseload + [ecx+k] cluster, and adjacent pushes (v1 FAIL).
// popTb site +6 baked in C (only site 0xf); alias base +0x4e20 lives in the
// map. gClipCount -> _globalSecondarySurface+0x4.
extern long gClipCount;   /* map _gClipCount=_globalSecondarySurface+0x4 */
extern short popTb[];     /* map _popTb=_tempYLR+0x4e20 */
extern int gSetClipBox(int a, int b, int c, int d);  /* map _gSetClipBox=@G_SetClipBox@16 */

__declspec(naked) void __fastcall G_PopClipBox(void)
{
    __asm {
        mov eax, dword ptr [gClipCount]
        dec eax
        mov dword ptr [gClipCount], eax
        movsx edx, word ptr popTb[eax*8+6]
        lea ecx, popTb[eax*8]
        push edx
        movsx eax, word ptr [ecx+4]
        movsx edx, word ptr [ecx+2]
        movsx ecx, word ptr [ecx]
        push eax
        call gSetClipBox
        ret
    }
}