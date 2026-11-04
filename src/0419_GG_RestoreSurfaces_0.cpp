/*
 * w44D_5d9d0_v1.cpp — @GG_RestoreSurfaces@0 @ 0x45d9d0 (112 B, fpo/esp,
 * locals=4, cbRegs=1).  Restore() is thiscall (QAEHXZ): .cpp member decl.
 * Primary surface Restore + SetRect/ClipCursor clip-rect dance from
 * grMode WORD fields (+0xa,+0xc), then secondary surface Restore.
 * FA quirk: 90 nop after the first test, unused push ebx.
 */
struct RECT { long left, top, right, bottom; };
struct CDirDrawSurface { char Restore(void); };

extern "C" {
__declspec(dllimport) int __stdcall SetRect(RECT *r, int left, int top,
                                            int right, int bottom);
__declspec(dllimport) int __stdcall ClipCursor(const RECT *r);
}

extern void *globalPrimarySurface;
extern void *globalSecondarySurface;
extern short grMode[];

unsigned char __fastcall GG_RestoreSurfaces(void)
{
    RECT r;
    if (globalPrimarySurface != 0) {
        if (((CDirDrawSurface *)globalPrimarySurface)->Restore() == 0)
            return 0;
        SetRect(&r, 0, 0, grMode[5], grMode[6]);
        ClipCursor(&r);
    }
    if (globalSecondarySurface != 0) {
        if (((CDirDrawSurface *)globalSecondarySurface)->Restore() == 0)
            return 0;
    }
    return 1;
}