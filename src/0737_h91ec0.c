// w43G chunk rva 0x91ec0 (80 B): dialog G_Box band wrapper.
// FA: mov ecx,0x5e; call @G_SetColor@4; then 4x (a1 reload of ?curDialog@@3PAUDIALOG@@A,
// movsx word field, +/- const, push) -> call _G_Box@16; ret. Tail pad 05 00000000 8da424.
// Push order: fE-0x28, fC-0x28, fA+0x14, f8+0x14 => args (f8+0x14, fA+0x14, fC-0x28, fE-0x28).
// Volatile pointer read to force FA's 4 separate a1 reloads (CSE killer).

extern void __fastcall G_SetColor(long c);
extern void __stdcall G_Box(long a, long b, long c, long d);

typedef struct {
    char pad[8];
    short f8;
    short fA;
    short fC;
    short fE;
} W43G_DLG;

extern volatile W43G_DLG *w43G_curDlg;

void w43G_91ec0_q(void)
{
    G_SetColor(0x5e);
    G_Box((long)w43G_curDlg->f8 + 0x14, (long)w43G_curDlg->fA + 0x14,
          (long)w43G_curDlg->fC - 0x28, (long)w43G_curDlg->fE - 0x28);
}