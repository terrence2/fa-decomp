/* ?InTextButton@@YIDJJ@Z @ rva 0x7df70 (80 B) — FA reads args from ecx/edx
 * (callers: movsx ecx/edx word loads, no stack args) => __fastcall.
 * v2: for-increment spelling to steer the jle-before-box-init order. */
extern long lastButton;              /* =_lastButton */
extern char buttonBoxes[];           /* =_buttonBoxes */
extern char __stdcall PointInBox(void *p, void *b);

char __fastcall w34d_itb(long x, long y)
{
    struct { short xx, yy; } p;
    long i;
    char *b;
    p.xx = (short)x;
    p.yy = (short)y;
    b = buttonBoxes;
    for (i = 0; i < lastButton; i++, b += 8) {
        if (PointInBox(&p, b))
            return (char)(i + 1);
    }
    return 0;
}