/* _G_PatLine@20 @ rva 0x964b0 (dec 614832), size 0x60 (91 code B + 90 +
 * pad tail). stdcall 5 args. FA holds arg2..arg5 in esi/edi/ebx/ebp,
 * copies them into a 4-int local block (L3..L0 = x2@-4, x3@-8, x4@-0xc,
 * x5@-0x10), passes descending pointers to _G_ClipLine (cdecl, baked
 * rel32 @0x3b, no .reloc; caller pops 0x10), and on TRUE forwards
 * a1..a5 (a1 re-read from [esp0+4]) to _G_UPatLine@20 (stdcall, baked
 * rel32 @0x50, pops its own args). Both calls unreloc'd in FA.
 */
extern char __cdecl G_ClipLine(char *, char *, char *, char *);  /* FA tests al,al */
extern void __stdcall G_UPatLine(int, int, int, int, int);

void __stdcall G_PatLine(int a1, int a2, int a3, int a4, int a5)
{
    int x2, x3, x4, x5;
    x2 = a2;
    x3 = a3;
    x4 = a4;
    x5 = a5;
    if (G_ClipLine(&x2, &x3, &x4, &x5) == 0)
        return;
    G_UPatLine(a1, a2, a3, a4, a5);
}