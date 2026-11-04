/* 0x861f0 _DialogShow@0 0xa0 — v3: volatile on the VARIABLE (dlg double-load),
 * pre-test + Lbody goto loop (no CL rotation), w stays in esi, ax re-and'd.
 */
extern long __fastcall MMAccessR(long arg);
extern void __stdcall G_Blit(long a1, long a2, long a3, long a4, long cb,
                             long a6, long a7, long a8, long a9);
extern void __cdecl w43D_dsA(void);
extern void __stdcall w43D_dsB(void *w);
extern void __stdcall DialogDraw(void *w);
extern void __cdecl w43D_dsE(void);
extern void * * volatile w43D_dlg;
extern void * * w43D_last;
extern unsigned long w43D_cb;
extern unsigned char firstDraw;

void __stdcall DialogShow(void)
{
    volatile unsigned char *d1, *d2;
    unsigned long v;
    unsigned short ax;
    void *w;
    w43D_dsA();
    d1 = (volatile unsigned char *)w43D_dlg;
    d2 = (volatile unsigned char *)w43D_dlg;
    w43D_last = 0;
    v = *(unsigned long *)(d1 + 0x1a);
    d1 += 0x1a;
    if (v == 0) {
        v = *(unsigned long *)(d2 + 0x16);
        *(unsigned long *)d1 = v;
        goto d3;
    }
    G_Blit(0, MMAccessR(v), 0, 0, (long)w43D_cb,
           (long)*(short *)(d2 + 8), (long)*(short *)(d2 + 0xa),
           (long)*(short *)(d2 + 0xc), (long)*(short *)(d2 + 0xe));
d3:
    w = *(void * volatile *)((char *)w43D_dlg + 4);
    ax = (unsigned short)(*(unsigned short *)w & 0x7fff);
    if (ax == 0xa)
        goto exit;
Lbody:
    if (ax == 7)
        w43D_dsB(w);
    DialogDraw(w);
    w = *(void **)((char *)w + 2);
    ax = (unsigned short)(*(unsigned short *)w & 0x7fff);
    if (ax != 0xa)
        goto Lbody;
exit:
    firstDraw = 0;
    w43D_dsE();
    return;
}