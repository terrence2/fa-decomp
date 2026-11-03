/* rva 355328 v2: stage 255 in the result reg BEFORE the > test; r declared
 * after t so t lands in a non-ax register (cx); return r */
short __cdecl w31b_56c00_v2(short s)
{
    short t = s;
    short r;

    if (t < 0)
        return 0;
    r = 255;
    if (t > 255)
        return r;
    r = t;
    return r;
}