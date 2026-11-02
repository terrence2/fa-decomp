#pragma optimize("y", off)
void CopySB8(void *src, void *dst, int step)
{
    int i;
    for (i = 0; i < 4; i++) {
        *(long *)dst = *(long *)src;
        src = (char *)src + 4;
        dst = (char *)dst + step;
    }
}