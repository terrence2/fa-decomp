/* FA chunk @Close@4 rva 0xa9e60 (96 B) — wave 33 batch E probe v2.
   v2: CloseHandle declared dllimport (FA calls via IAT ff 15), no (short)
   cast on the result (FA compares the full eax with 83 f8), and the second
   false exit goto-sourced to a shared trailing ret0 block. FA stores
   dosError = -1 as a word before pushing esi. */
extern void *handles32[];
extern short openHandles;
extern short dosError;
__declspec(dllimport) unsigned long __stdcall CloseHandle(unsigned long h);

char __fastcall Close(short h)
{
    void *v;
    void **slot;
    short oh;
    dosError = -1;
    v = handles32[h];
    slot = &handles32[h];
    if (v == 0)
        return 0;
    if (CloseHandle((unsigned long)v) != 1)
        goto ret0;
    oh = openHandles;
    *slot = 0;
    oh--;
    dosError = 0;
    openHandles = oh;
    return 1;
ret0:
    return 0;
}