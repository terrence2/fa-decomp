// _DialogSetRocker@8 @ rva 0x87520 (48 B) — shell-alloc guard pair, dialog
//   ptr via fastcall DialogGetPtr(param1), rocker word param2 (66 8b 4c 24 08)
//   stored to dialog+0x20 (mov [eax+0x20],cx with the push eax BEFORE the
//   store — the DialogDraw arg-push schedules first), then DialogDraw /
//   PopShellAlloc, ret 8.
extern void __stdcall PushShellAlloc(void);
extern void *__fastcall DialogGetPtr(int idx);
extern void __stdcall DialogDraw(void *d);
extern void __stdcall PopShellAlloc(void);

void __stdcall DialogSetRocker_q(int dlg, unsigned short val)
{
    void *d;
    PushShellAlloc();
    d = DialogGetPtr(dlg);
    *(unsigned short *)((char *)d + 0x20) = val;
    DialogDraw(d);
    PopShellAlloc();
}