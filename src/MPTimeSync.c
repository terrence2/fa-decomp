// ?MPTimeSync@@YGXXZ @ rva 0x6b420 (32 B) — FA asm: a1 <_numComputers>/
//   83 f8 01/74 06 (ret when ==1)/ff 25 <?MP_Synchronize@@3P6AXXZA> (tail
//   jmp through the function-pointer variable)/c3.  Plain C reproduces it
//   exactly: first read of the global lands in eax (a1 moffs, wave-5 rule)
//   and CL 4.2 emits the last void indirect call as a tail jmp [ptr]
//   (d63-family).  Probe build/w4probe/w19_mptimesync_v1.obj — exact.
extern long numComputers;
extern void (*mpSyncFn)(void);      /* ?MP_Synchronize@@3P6AXXZA */

void __stdcall MPTimeSync_q(void)
{
    if (numComputers == 1)
        return;
    mpSyncFn();
}