// __CopyMan @ rva 0xdfa10 — copy 12 bytes (3 dword steps); the src pointer
//   local declared first pins eax=src/esi-temp/edx-count scheduling (d180)
void CopyMan_q(void *dst, void *src)
{
    char *s = (char *)src;
    char *d = (char *)dst;
    int n = 3;
    do
    {
        *(long *)d = *(long *)s;
        s = (char *)s + 4;
        d = (char *)d + 4;
    } while (--n != 0);
}
