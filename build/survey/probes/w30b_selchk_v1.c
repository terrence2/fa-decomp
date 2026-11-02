/* gap chunk rva 0xbf700 (32 B): fastcall bool — [ecx]==4 && *(int*)(p+0x34) > 0x3a00.
   FA: cmp BYTE [ecx],4 / jne / mov eax,[ecx+0x34] / cmp eax,0x3a00 / jle /
   mov al,1 / ret / xor al,al / ret. */
unsigned char __fastcall w30b_selchk(char *p)
{
    if (p[0] != 4)
        return 0;
    if (*(long *)(p + 0x34) <= 0x3a00)
        return 0;
    return 1;
}