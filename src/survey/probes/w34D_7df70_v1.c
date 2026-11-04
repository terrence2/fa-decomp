/* ?InTextButton@@YIDJJ@Z @ rva 0x7df70 (80 B) — FA reads args from ecx/edx
 * (both callers emit movsx ecx/edx word-loads then e8, no stack args)
 * => __fastcall. Builds a 2-word {x,y} local, loops _buttonBoxes (8 B
 * stride), returns i+1 on PointInBox(&p, box) else 0. */
extern long w34d_lb;                      /* =_lastButton */
extern char w34d_bb[];                    /* =_buttonBoxes */
extern char __stdcall PointInBox(void *p, void *b);

char __fastcall w34d_itb(long x, long y)
{
    struct { short xx, yy; } p;
    long i;
    char *b;
    p.xx = (short)x;
    p.yy = (short)y;
    b = w34d_bb;
    for (i = 0; i < w34d_lb; i++) {
        if (PointInBox(&p, b))
            return (char)(i + 1);
        b += 8;
    }
    return 0;
}