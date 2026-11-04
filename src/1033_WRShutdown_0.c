// _WRShutdown@0 @ rva 0xb0a70 (32 B) — fastcall-MMFreePtr the layer-file
// header pointer, then clear hdrPtr (a3 moffs eax store) and tint[4] (a2
// moffs al store, addend +4 baked in the disp). Plain C reproduces the
// xor/a3/a2 zero pair here (probe w11a_02_wsh1, byte-exact) unlike the
// wave-10 OBJStopAdding case, so no asm escape needed.
extern void *__fastcall MMFreePtr(void *p);
extern void *hdrPtr;
extern char tint[];

void __stdcall WRShutdown_q(void)
{
    MMFreePtr(hdrPtr);
    hdrPtr = 0;
    tint[4] = 0;
}