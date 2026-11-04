/* unnamed chunk @ rva 0x4e18c0 (42 B) v2: inc-mem dst increment */
void __cdecl w37gCopyChar(char *src, char **dst, int *cnt)
{
    char c;
    if (*cnt) {
        do {
            c = *src;
            if (c == 0) break;
            **dst = c;
            ++*dst;
            src++;
            (*cnt)--;
        } while (*cnt);
    }
}