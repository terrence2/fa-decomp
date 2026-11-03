/* FA chunk @Close@4 rva 0xa9e60 (96 B) — wave 33 batch E probe v1.
   Fastcall short handle-slot index in cx. -1s _dosError, loads/caches the
   slot, CloseHandle()s, on success nulls the slot and decrements
   openHandles (word global). FA stores dosError = -1 as a word before
   pushing esi, and re-derives &handles32[h] both as a load and a lea.
   Map _handles32=?handles32@@3PAPAXA, _openHandles=?openHandles@@3FA. */
extern void *handles32[];
extern short openHandles;
extern short dosError;
unsigned long __stdcall CloseHandle(unsigned long h);

char __fastcall Close(short h)
{
    void *v;
    void **slot;
    short oh;
    short r;
    dosError = -1;
    v = handles32[h];
    slot = &handles32[h];
    if (v == 0)
        return 0;
    r = (short)CloseHandle((unsigned long)v);
    if (r != 1)
        return 0;
    oh = openHandles;
    *slot = 0;
    oh--;
    dosError = 0;
    openHandles = oh;
    return 1;
}