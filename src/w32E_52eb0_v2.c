extern int __fastcall NextString(int pv, int n);

int __fastcall w32e_52eb0_v2(char *p)
{
    char c;
    if (p == 0)
        return 0;
    c = *p;
    if (c == 7)
        return NextString(*(int *)(p + 5), 2);
    return NextString(*(int *)(p + 1), 2);
}