/* probe w45D_aff20 (FA 0x4aff20, 96B): 3-channel palette lerp, stdcall ret 0xc */
void __stdcall w45D_aff20(unsigned char *dst, unsigned char *src, long n)
{
    long a, b;
    if (n > 0) {
        a = dst[0]; b = src[0];
        dst[0] = ((b - a) * n >> 8) + a;
        a = dst[1]; b = src[1];
        dst[1] = ((b - a) * n >> 8) + a;
        a = dst[2]; b = src[2];
        dst[2] = ((b - a) * n >> 8) + a;
    }
}