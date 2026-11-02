// 0x98490 — v2: FA loaded arg2 (wrapper) into esi FIRST (left operand of
// the % expression); ebx = arg1 (queue)
void __cdecl w28c_overwriteQ(long *sq, long *pw)
{
    long rem;

    rem = pw[1] % sq[2];
    memcpy((void *)((char *)sq[5] + (rem * 48)), (void *)pw, 48);
    *(long *)((char *)sq[5] + (rem * 48) + 0x10) = 1;
}
