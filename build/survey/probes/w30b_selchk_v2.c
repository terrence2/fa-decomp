/* gap chunk rva 0xbf700 (32 B): fastcall bool — v2 volatile load to defeat
   setg fusion + compare-to-memory fold. */
unsigned char __fastcall w30b_selchk(char *p)
{
    if (p[0] != 4)
        return 0;
    if (*(volatile long *)(p + 0x34) > 0x3a00)
        return 1;
    return 0;
}