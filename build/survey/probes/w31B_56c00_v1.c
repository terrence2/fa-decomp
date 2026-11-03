/* rva 355328 (0x56c00) 32 B FPO/esp gap chunk
 * mov cx,[esp+4]; test cx,cx; jge L; xor ax,ax; ret;
 * L: mov ax,0xff; cmp cx,0xff; jg R; mov eax,ecx; ret  (cdecl, word-width param)
 * signed-16 clamp: s<0 -> 0; s>255 -> 255; else s */
int __cdecl w31b_56c00(short s)
{
    short t = s;

    if (t < 0)
        return 0;
    if (t > 255)
        return 255;
    return t;
}