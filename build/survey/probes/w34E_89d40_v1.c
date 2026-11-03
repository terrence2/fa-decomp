/* w34E_89d40 @ rva 0x89d40 (32 B) — cdecl: two word adds from curDialog
 * fields +8/+0xa into *(short*)p, with curDialog loaded twice (a1 then
 * 8b 15 edx) — statement pair with reload of the pointer. */
extern char *w34E_curDlg;       /* =?curDialog@@3PAUDIALOG@@A */

void __cdecl w34E_89d40(void *p)
{
    char * volatile d;
    d = w34E_curDlg;
    *(short *)p += *(short *)(d + 8);
    d = w34E_curDlg;
    *(short *)((char *)p + 2) += *(short *)(d + 0xa);
}