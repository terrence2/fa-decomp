extern void *__fastcall MMAccessW(void *h);
void RemapAdd(void *h, long add)
{
    char *v, *p, *end;
    if (add == 0) return;
    v = (char *)MMAccessW(h);
    p = *(char **)(v + 0xa);
    end = p + *(long *)(v + 0xe);
    while (p < end) {
        *p += (char)add;
        ++p;
    }
}