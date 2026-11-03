/* w32H_0e910_v1: unnamed chunk @ rva 0xe910 (32 B). */
void __fastcall w32h_0e910(void *dst);
extern char buttonZoomOut[];

void __fastcall w32h_0e910(void *dst) {
    extern void *memcpy(void *, const void *, unsigned);
    if (buttonZoomOut[0xc8])
        memcpy(dst, &buttonZoomOut[8], 0xc0);
}
