// _CTDo_restart @ rva 0x64c10 — if the restart flag byte is clear, tail-jmp
//   into the unnamed restart entry (gap anchor 0x463e90) with fastcall 1
//   (probe d65: fastcall decl gives mov ecx,1 + e9; cdecl gave push/e8).
extern char serviceTicks[];
extern void __fastcall t3e90(int f);

void CTDo_restart_q(void)
{
    if (*(char *)((char *)serviceTicks + 0xec) == 0)
        t3e90(1);
}
