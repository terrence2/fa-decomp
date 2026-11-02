// ?updateQueueHead@@YAXAAUSERIAL_QUEUE@@J@Z @ rva 0x98410 (32 B) — FA asm
//   (no relocs at all): 8b 44 24 08 (arg2 j = eax)/85 c0 (test)/7c 0a
//   (jl ret)/8b 4c 24 04 (arg1 q = ecx)/99 (cdq)/f7 79 08 (idiv [ecx+8])/
//   89 11 (mov [ecx],edx — remainder)/c3 (Y-mangle = cdecl, bare ret).
//   if (j >= 0) q->head = j mod q->capacity.  Plain C: CL keeps j in eax
//   across the test, loads the ref pointer into ecx for the divide, and
//   stores the edx remainder — same plan.  First draft fell to __stdcall
//   (c2 08 ret); b20f_updateQueueHead (cdecl) exact.  Probe
//   build/w4probe/b20f_updateQueueHead.obj — exact (no fixups).
void __cdecl updateQueueHead_q(void *q, long j)
{
    if (j >= 0)
        *(long *)q = j % ((long *)q)[2];
}