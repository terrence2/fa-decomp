// Wave 46 batch C entry 2: _DialogFadeout@0 @ rva 648800 (0x9e660), 176 B
// Fades curPalette toward black over timer ticks: per-tick struct-copy of
// fadePalette into curPalette (rep movsd = struct assignment), scaled level,
// WRBlackenPalette + G_SetPalette until level saturates 0x100, then clears
// fadePalette (rep stosd) and flushes the screen.
// FPO esp, locals=0, params=0, cbProlog=11, cbRegs=3 (ebx timebase, esi level)
typedef struct { unsigned long d[0xc0]; } W46CPAL;
extern W46CPAL fadePalette;                 /* -> _fadePalette */
extern W46CPAL curPalette;                  /* -> _curPalette */
extern unsigned long timerTicks;            /* -> _timerTicks */
extern short w46c_gw; /* map _w46c_gw=_grMode+0xa */
extern short w46c_gh; /* map _w46c_gh=_grMode+0xc */
extern void __fastcall WRInt(long n);
extern void __stdcall WRBlackenPalette(W46CPAL *pal, long n, long level);
extern void __stdcall G_SetPalette(W46CPAL *pal, long from, long to, long flag);
extern void __fastcall G_SetColor(long c);
extern void __stdcall G_URect(long x, long y, long w, long h);
extern void __stdcall ScreenDirty(void);
extern void __fastcall G_Flush(long n);

void __stdcall DialogFadeout(void)
{
    unsigned long elapsed;
    short s;
    long t;

    t = timerTicks;
    WRInt(0);
    do {
        curPalette = fadePalette;
        elapsed = (timerTicks - t) * 0x100;
        s = (short)(elapsed / 14u);
        if (s > 0x100)
            s = 0x100;
        WRBlackenPalette(&curPalette, 0x100, s);
        G_SetPalette(&curPalette, 0, 0x100, 1);
    } while (s < 0x100);
    memset(&fadePalette, 0, 0x300);
    G_SetColor(0);
    G_URect(0, 0, w46c_gw, w46c_gh);
    ScreenDirty();
    G_Flush(0);
}