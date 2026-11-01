// @NextString@8 @ rva 0x11dc0 — walks n NUL-terminated strings forward.
//   `while (n-- > 0)` (probe d113 exact) gives FA's post-dec loop shape —
//   the n>0+n-- form canonicalized to dec/jne.
char *__fastcall NextString_q(char *s, int n)
{
    char *p = s;
    while (n-- > 0)
        p += strlen(p) + 1;
    return p;
}
