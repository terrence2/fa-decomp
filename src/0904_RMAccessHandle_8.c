extern int __stdcall rmAccess_(int a, int b);
int __stdcall RMAccessHandle(int a, int b)
{
    int p;
    p = rmAccess_(a, b);
    if (p != 0)
        return *(long *)(p + 0xf);
    return 0;
}
