// w29b A: _DialogEnableItem@12 @ rva 0x8b250 (80 B incl. 5-byte 0500000000 tail pad)
// stdcall(3 args). FA body:
//   dlg = DialogGetPtr(hwnd) (fastcall, ecx)
//   mask = *(unsigned short*)dlg
//   enable: bit15 set -> mask &= 0x7fff, bit15 clear -> return
//   !enable: bit15 set -> return, else mask |= 0x8000
//   store mask; if (redraw) { g4f8488 = 1; DialogDraw(dlg)@stdcall; g4f8488 = 0; }
// g4f8488 = _checkRightButton+0x4 data byte.
extern void *__fastcall DialogGetPtr_a(void *hwnd);
extern void __stdcall DialogDraw_a(void *dlg);
extern unsigned char g4f8488_a;

void __stdcall DialogEnableItem_q(void *hwnd, int enable, int redraw)
{
    void *dlg;
    unsigned short mask;
    dlg = DialogGetPtr_a(hwnd);
    mask = *(unsigned short *)dlg;
    if (enable) {
        if (mask & 0x8000)
            mask &= 0x7fff;
        else
            return;
    } else {
        if (mask & 0x8000)
            return;
        mask |= 0x8000;
    }
    *(unsigned short *)dlg = mask;
    if (redraw) {
        g4f8488_a = 1;
        DialogDraw_a(dlg);
        g4f8488_a = 0;
    }
}