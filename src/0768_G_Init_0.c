/* @G_Init @ 0x95470 (176 B): graphics-context init (fastcall, 0 args).
 * sequence:
 *   MMPushAllocId(0);                        [33 c9 + call @4]
 *   vrHelmet = 0;                            [c6 05 1c3355 00 byte store]
 *   if (!GG_InitMode())                      [call @0, test al]
 *       ErrorExit(w46g_vhz, w46g_ylr);       [push ylrval; push 0x4fcf34; cdecl +8]
 *   G_AllocSurfaceBitmap(grMode.wa, grMode.wc);   [66 a1 wc; 66 8b 0d wa; push; push; @8]
 *   surf: xor edx,edx; mov ecx,eax; MMLockW(ecx, 0);  [@MMLockW@8 fastcall]
 *   mainBitmap = result; cb = result;        [a3 00cf4f00; a3 fcce4f00]
 *   w46g_cbp: mov byte ds:0x4fcef8,1 is AFTER MMPopAllocId (see bottom)
 *   G_SetFullClipBox(); G_InitLineStats(); G_InitCircles();
 *   G_SetColor(0xff);                        [b9 ff000000 + call @4]
 *   tm = MMLockW(G_AllocBitmap(0x1e, 0x1e, 0x8000), 0);  [push 0x8000; push 0x1e; push 0x1e; stdcall]
 *   w46g_tm = result;                        [a3 64335500]
 *   xor eax,eax; w46g_cf = 0; w46g_crt = 0;  [a3 x2]
 *   MMPopAllocId();                          [call @0]
 *   w46g_cbp = 1;                            [c6 05 f8ce4f00 01]
 * w46g_ylr  is the dword at _tempYLR+0x4e70   (0x553128)
 * w46g_vhz  is the literal _vHzMod+0x4        (0x4fcf34)
 * w46g_cbp  is the byte at _cb-0x4            (0x4fcef8)
 * w46g_tm   is ?tempBitmap@@3PAUT_BITMAP@@A   (0x553364)
 * w46g_cf   is ?cFont@@3PAUFONT@@A            (0x553328)
 * w46g_crt  is ?cRemapTable@@3PAEA            (0x558414)
 */
extern unsigned char vrHelmet;              /* _vrHelmet */
extern long mainBitmap;                     /* _mainBitmap */
extern long cb;                             /* _cb */
extern struct { unsigned char pad[0xa]; short wa; short wc; } grMode;
extern void __fastcall MMPushAllocId(long id);
extern char __fastcall GG_InitMode(void);
extern char __fastcall GG_GetMode(void);
extern void ErrorExit(char *s, long v);
extern long __stdcall G_AllocSurfaceBitmap(short a, short b);
extern long __fastcall MMLockW(void *b, long a2);
extern void __fastcall G_SetFullClipBox(void);
extern void __stdcall G_InitLineStats(void);
extern void __stdcall G_InitCircles(void);
extern void __fastcall G_SetColor(long c);
extern long __stdcall G_AllocBitmap(long w, long h, long a3);
extern void __fastcall MMPopAllocId(void);
extern long w46g_ylr;                       /* _tempYLR+0x4e70 */
extern char w46g_vhz[];                     /* _vHzMod+0x4 */
extern char w46g_cbp;                       /* _cb-0x4 */
extern long w46g_tm;                        /* ?tempBitmap@@3PAUT_BITMAP@@A */
extern long w46g_cf;                        /* ?cFont@@3PAUFONT@@A */
extern unsigned char *w46g_crt;             /* ?cRemapTable@@3PAEA */

void __fastcall G_Init(void)
{
    MMPushAllocId(0);
    vrHelmet = 0;
    if (!GG_InitMode())
        ErrorExit(w46g_vhz, w46g_ylr);
    GG_GetMode();
    mainBitmap = MMLockW(G_AllocSurfaceBitmap(grMode.wa, grMode.wc), 0);
    cb = mainBitmap;
    G_SetFullClipBox();
    G_InitLineStats();
    G_InitCircles();
    G_SetColor(0xff);
    w46g_tm = MMLockW(G_AllocBitmap(0x1e, 0x1e, 0x8000), 0);
    w46g_cf = 0;
    w46g_crt = 0;
    MMPopAllocId();
    w46g_cbp = 1;
}