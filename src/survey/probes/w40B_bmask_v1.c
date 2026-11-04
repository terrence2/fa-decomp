/* rva 0xa8fe0 (dec 692192), 80 B unnamed, 1 arg, no fixups, fpo/esp frame.
 * FA: ecx = [esp+4]; band1: mov eax,ecx; and eax,0xe0000000; cmp eax,0xc0000000;
 *   jne B2; mov eax,0xffffff00; ret.
 * band2: mov eax,ecx; and eax,0xc0000000; cmp eax,0x80000000; jne B3;
 *   mov eax,0xffff0000; ret.
 * band3: and ecx,0x80000000 (81 e1); sub ecx,0x80000000 (81 e9);
 *   cmp ecx,1; sbb eax,eax; and eax,0xff000000; ret.
 * tail pad 13 B (8d9b 00000000 + 8da4 24000000).
 */
long w40b_bmask(long p)
{
    if ((p & 0xe0000000) == 0xc0000000)
        return 0xffffff00;
    if ((p & 0xc0000000) == 0x80000000)
        return 0xffff0000;
    return (unsigned long)((p & 0x80000000) - 0x80000000) < 1
               ? (long)0xff000000 : 0;
}