void *memset(void *d, int v, unsigned int n);
extern char fmtZone[];       /* _buttonBoxes+0xc8 */
extern char fmtText[];       /* _fmtText */

void FormatInit_q(void)
{
    char *p;
    memset(fmtZone, 0, 0x38);
    p = fmtText;
    do {
        *(unsigned long *)p = 0;
        p += 0x44;
        *(unsigned long *)(p - 0x20) = 0;
    } while ((unsigned long)p < (unsigned long)(fmtText + 0xcc));
}
