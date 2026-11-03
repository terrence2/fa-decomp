/* rva 125488 v3: p as long; whole compare one expression; char return */
char __stdcall w31b_1ea30_v3(long p)
{
    return *(long *)(*(long **)(p + 0x3c) + p) == 0x4c50;
}