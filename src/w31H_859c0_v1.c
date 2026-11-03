/* w31H_859c0 v1: FA bytes (rva 0x859c0, 25 B code + 7 B pad): xor ecx,ecx;
   mov eax,[esp+4]; loop: mov dl,[eax]; test dl,dl; jne L0; inc ecx; inc eax;
   cmp ecx,6; jl loop; mov al,1; ret; L0: xor al,al; ret.
   cdecl (ret w/o imm), 1 param, char-like return (al only). do-while with
   bottom cmp 6/jl, i++ before pointer advance (wave-19 idiom). */
char w31h_859c0(const char *p)
{
    int i = 0;
    do {
        if (*p) return 0;
        i++;
        p++;
    } while (i < 6);
    return 1;
}