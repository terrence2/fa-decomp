void *memset(void *, int, unsigned);

void __stdcall ZeroFrame_q(unsigned char *f, long w, long h, short val)
{
    memset(f, val, w * h);
}
