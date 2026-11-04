// _SMShutdown@0 @ rva 0x69690 (22 B) — FreeNames pattern: fastcall MMFreePtr
//   on the pointer field at _pilotsUpdated+0x2b4, then null it (probe d137).
extern void *pilotsUpdated[];
extern void __fastcall MMFreePtr(void *p);
void __stdcall SMShutdown_q(void)
{
    MMFreePtr(pilotsUpdated[0xad]);
    pilotsUpdated[0xad] = 0;
}
