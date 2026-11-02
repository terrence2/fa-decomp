/* gap chunk @ 0x8b330 (16B) — v1: *(p+0x24)=1 where p = *(long*)(arg+0x12) */
void w28b_gap160_g1(void *arg)
{
    long p = *(long *)((char *)arg + 0x12);
    *(unsigned char *)(p + 0x24) = 1;
}
