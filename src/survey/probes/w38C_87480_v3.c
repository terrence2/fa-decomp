/* w38C 0x87480 (160 B) _DialogMatchListString v3: 32-bit-and widening
 * (`long c = *(ushort*)q & 0x7fff` -> mov cx + and ecx per CL peephole),
 * stdcall DialogDraw, exact advance stage structure. */
extern void *__fastcall DialogGetPtr(long id);        /* @DialogGetPtr@4 */
extern void __stdcall DialogDraw(void *q);            /* ?DialogDraw@@YGXPAX@Z */
extern int strcmp(const char *, const char *);

unsigned short DialogMatchListString(long id, char *list)
{
    unsigned char *q;
    char *lp;
    long c;
    unsigned short i;
    unsigned char ch;

    q = DialogGetPtr(id);
    c = *(unsigned short *)q & 0x7fff;
    if (c != 4)
        return 0;
    lp = *(char **)(q + 0x20);
    i = 0;
    while (*lp) {
        if (strcmp(lp, list) == 0) {
            *(unsigned short *)(q + 0x1a) = i;
            DialogDraw(q);
            return i;
        }
        i++;
        do {
            ch = lp[1];
            lp++;
        } while (ch);
        ch = lp[1];
        lp++;
        if (ch)
            continue;
        break;
    }
    return 0xffff;
}