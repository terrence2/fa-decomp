extern void * __fastcall DialogGetPtr_a(void *hwnd);
extern void __stdcall DialogDraw_a(void *dlg);
extern unsigned char g4f8488_a;

void __stdcall DialogEnableItem_q(void *hwnd, unsigned char enable, unsigned char redraw)
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