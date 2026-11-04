/*
 * w44D_25db5_v1.c — unnamed @ 0x425db5 (103 B, fpo/esp, locals=1)
 * Fastcall(WORD id in cx, WORD_POINT *wp in edx).  Gate: id==0 ||
 * sub424cd6(id)==0 -> skip.  Screen-casts objPtrs[id]+0x11 into a local
 * WORD_POINT and draws a 5-arg PatLine (stack: color wp0+1 wp2+2
 * out.x+1 out.y+2 — right-to-left pushes).
 */
extern void **objPtrs;
extern unsigned char __fastcall w44dIs424cd6(unsigned short id);
extern void __fastcall w44dW2S(void *w, struct WPNT *o);
extern void __fastcall G_SetColor(int c);
extern void __stdcall G_PatLine(int c, int x1, int y1, int x2, int y2);

struct WPNT { short x, y; };

void __fastcall FA_25db5(unsigned short id, struct WPNT *wp)
{
    struct WPNT out;
    if (id == 0 || w44dIs424cd6(id) == 0)
        return;
    w44dW2S((char *)objPtrs[id] + 0x11, &out);
    G_SetColor(0x30);
    G_PatLine(0xf0f0f0f0, (int)wp->x + 1, (int)wp->y + 2,
              (int)out.x + 1, (int)out.y + 2);
}