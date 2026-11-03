/* rva 355328 v4: int return (mov eax,ecx shape = int copy of ecx);
 * r typed int so the in-range path is a full 32-bit reg copy */
int __cdecl w31b_56c00_v4(short s)
{
    short t = s;
    int r;

    if (t < 0)
        return 0;
    r = 255;
    if (t > 255)
        return r;
    r = t;
    return r;
}