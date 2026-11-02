#pragma optimize("y", off)
void CopySB8(void *src, void *dst, int step)
{
    *(long *)dst = *(long *)src;
    src = (char *)src + 4;
    dst = (char *)dst + step;
    *(long *)dst = *(long *)src;
    src = (char *)src + 4;
    dst = (char *)dst + step;
    *(long *)dst = *(long *)src;
    src = (char *)src + 4;
    dst = (char *)dst + step;
    *(long *)dst = *(long *)src;
}