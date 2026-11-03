/* rva 355328 v3: ternary spelled value-first after the neg test */
short __cdecl w31b_56c00_v3(short s)
{
    short t = s;

    if (t < 0)
        return 0;
    return (t > 255) ? 255 : t;
}