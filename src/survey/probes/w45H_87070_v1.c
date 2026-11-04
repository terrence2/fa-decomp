/* w45H 0x87070: dialog element walk (firstDraw/DialogDraw retrigger) */
typedef unsigned long ulong;
typedef unsigned short ushort;

extern void *curDialog;                     /* _curDialog = ?curDialog@@3PAUDIALOG@@A */
extern void __stdcall DialogDraw(void *);
extern char firstDraw;                      /* _firstDraw = _firstDraw */

ulong w45H_87070(ulong arg)
{
    char *e;
    char *found;
    ushort t;
    e = *(char **)((char *)curDialog + 4);
    found = 0;
    t = *(ushort *)e & 0x7fff;
    for (;;) {
        if (t == 1 || t == 5) {
            if (*(ushort *)(e + 0x17) == (ushort)arg) {
                if (*(char *)(e + 0x16)) {
                    *(char *)(e + 0x16) = 0;
                    if (t == 1)
                        found = e;
                    else if (!firstDraw)
                        DialogDraw(e);
                }
            }
        }
        e = *(char **)(e + 2);
        t = *(ushort *)e & 0x7fff;
        if (t == 0xa)
            break;
    }
    return (ulong)found;
}