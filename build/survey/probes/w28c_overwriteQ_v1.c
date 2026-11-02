// 0x98490 ?overwriteQueue@@YAXAAUSERIAL_QUEUE@@AAUSERIAL_PACKET_WRAPPER@@@Z (64 B) — v1
/* queue block (48 B) is overwritten into the wrapper ring buffer at
   rem*48; packet header +0x10 dword set to 1 */
void __cdecl w28c_overwriteQ(long *sq, long *pw)
{
    long rem;

    rem = sq[1] % pw[2];
    memcpy((void *)((char *)pw[5] + (rem * 48)),
           (void *)sq, 48);
    *(long *)((char *)pw[5] + (rem * 48) + 0x10) = 1;
}
