/* w37F v2 rva 0xdb670: int* arithmetic (d + 3*cnt), memory-operand compare */
extern int __XcptActTabCount;

void *w37f_db670(int key, int *d)
{
    int *p;
    p = d;
    do {
        if (*p == key)
            break;
        p += 3;
    } while (d + 3 * __XcptActTabCount > p);
    if ((unsigned)(*p - key) < 1U)
        return p;
    return 0;
}