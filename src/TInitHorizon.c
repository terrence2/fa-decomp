extern void *__stdcall RMAccess(void *p, unsigned long flags);
extern unsigned char ambientProcs[];
extern unsigned char PLhook[];
extern char computerFlight;
extern unsigned char PLthrustPitch[];
void __stdcall T_InitHorizonProc(void)
{
    *(void **)(PLhook + 4) = RMAccess(ambientProcs + 0x54, 0x8000);
    *(void **)((char *)&computerFlight + 4) = RMAccess(ambientProcs + 0x4c, 0x8000);
    *(void **)(PLthrustPitch + 4) = RMAccess(ambientProcs + 0x44, 0x8000);
}