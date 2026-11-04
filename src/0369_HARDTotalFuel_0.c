/* _HARDTotalFuel@0 @ 0x53090 (80 B)
   FA: sub esp,8; [hidden] mov dword [esp],0x7fffffff (buf[0] sentinel);
   push esi; xor esi,esi; loop: lea eax,[esp+4]; push 0xff/push 0x8/push eax;
   call _HARDFindStore@12 (stdcall 3-arg); cmp eax,-1; je exit; lea ecx,[esp+8];
   push 0/push ecx/push eax; call _HARDPtrs@12; mov eax,[esp+8] (=buf[1]);
   add esi,[eax+6]; jmp loop; exit: mov eax,esi; pop esi; ret.
   FPO locals=2 dwords (buf), total in esi; cbProlog=12 cbRegs=1. */
extern int __stdcall HARDFindStore(unsigned long *p, int a, int b);
extern void __stdcall HARDPtrs(unsigned long idx, unsigned long *out, int z);

int __stdcall HARDTotalFuel(void)
{
    unsigned long buf[2];
    int total = 0;
    buf[0] = 0x7fffffff;
    for (;;) {
        long i = HARDFindStore(buf, 8, 0xff);
        if (i == -1)
            break;
        HARDPtrs(i, &buf[1], 0);
        total += *(long *)(buf[1] + 6);
    }
    return total;
}