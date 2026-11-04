// w41C candidate 0x45950 (rva 285008, 40 B code + 2x8d642400 pad) —
// unnamed stdcall(@8) wrapper: RMAccessHandle(p1, p2) then
// seqIgnoreTicks += timerTicks - before (tick cost accounting).  FA:
//   8b 44 24 08 (mov eax,[esp+8] = p2) / 56 (push esi) /
//   8b 35 <_timerTicks> (mov esi,ds:_timerTicks) / 50 (push eax) /
//   8b 4c 24 0c (mov ecx,[esp+0xc] = p1) / 51 (push ecx) /
//   e8 _RMAccessHandle@8 / 8b 15 <_timerTicks> (mov edx,ds:) /
//   2b d6 (sub edx,esi) / 5e (pop esi) / 01 15 <?seqIgnoreTicks@@3KA>
//   (add ds:seqIgnoreTicks,edx) / c2 08 00.
extern long timerTicks;
extern long w41C_seqTicks;      /* map FROM -> ?seqIgnoreTicks@@3KA */
extern long __stdcall RMAccessHandle(long id, long flags);

void __stdcall w41C_RMSeqAccess(long p1, long p2)
{
    long before = timerTicks;
    RMAccessHandle(p1, p2);
    w41C_seqTicks += timerTicks - before;
}