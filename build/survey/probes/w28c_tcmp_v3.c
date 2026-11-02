// 0xa7640 — v3: word reads with movsx (FA 0f bf), hi-load-shl-lo-add order
long __cdecl w28c_tcmp(char *a, char *b)
{
    long k1, k2;

    k1 = (long)(short)*((short *)a + 1);
    k1 <<= 16;
    k1 += (long)(short)*(short *)a;
    k2 = (long)(short)*((short *)b + 1);
    k2 <<= 16;
    k2 += (long)(short)*(short *)b;
    if (k1 < k2) return -1;
    return k1 > k2;
}
