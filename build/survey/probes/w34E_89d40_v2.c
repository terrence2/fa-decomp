/* w34E_89d40 @ rva 0x89d40 (32 B) — v2: volatile GLOBAL (no volatile
 * local => no stack slot): a1/8b 15 double load of ?curDialog@@3PAU...*/
extern char * volatile w34E_curDlg;   /* =?curDialog@@3PAUDIALOG@@A */

void __cdecl w34E_89d40(void *p)
{
    *(short *)p += *(short *)(w34E_curDlg + 8);
    *(short *)((char *)p + 2) += *(short *)(w34E_curDlg + 0xa);
}