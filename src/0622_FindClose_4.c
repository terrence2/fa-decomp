// __FindClose@4 @ rva 0x789f0 — shared push of the handle before the flag byte
// deref; false path defers to G_FindClose, true path calls the gap anchor and
// forces the 1 result (probe w11b_09, byte-exact; polarity: zero-check returns
// callee result directly, char return keeps mov al,1)
extern int __stdcall G_FindClose(void *h);
extern int __cdecl fcAnchor_(void *h);
char __stdcall FindClose_q(void *h)
{
    if (*(char *)((char *)h + 4) == 0)
        return (char)G_FindClose(h);
    fcAnchor_(h);
    return 1;
}