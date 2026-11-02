/* _G_TileShutDown @ 0x47093 (dec 290963) — v2: /Od recipe (twin _G_TileInit
 * winning entry: flags /c /Od /Gy /G5 + insert the CL-dropped empty-else
 * join jmp e9+0 at FA off 0x28; je rel32 is reloc-masked so target label
 * self-corrects after the insert).
 */
void __fastcall MMFreeHandle(void* h);
extern void* bltBuffer;

void G_TileShutDown_v2(void)
{
    if (bltBuffer) {
        MMFreeHandle(bltBuffer);
        bltBuffer = 0;
    }
}