/* ?InTextButton@@YIDJJ@Z @ rva 0x7df70 (80 B) — v3: index spelling
 * buttonBoxes + (i << 3) instead of a walked pointer. */
extern long lastButton;              /* =_lastButton */
extern char buttonBoxes[];           /* =_buttonBoxes */
extern char __stdcall PointInBox(void *p, void *b);

char __fastcall w34d_itb(long x, long y)
{
    struct { short xx, yy; } p;
    long i;
    p.xx = (short)x;
    p.yy = (short)y;
    for (i = 0; i < lastButton; i++)
        if (PointInBox(&p, buttonBoxes + (i << 3)))
            return (char)(i + 1);
    return 0;
}