int __stdcall MultDiv32(int a, int b, int c)
{
    volatile int t = a * b / c;
    return t;
}
