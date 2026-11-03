/* rva 125488 (0x1ea30) 32 B FPO/esp gap chunk
 * mov eax,[esp+4]; mov ecx,[eax+0x3c]; cmp dword [ecx+eax],0x4c50 (hidden!);
 * sete al; ret 4  (stdcall 1 param, char-width return: only al touched */
int __stdcall w31b_1ea30(char *p)
{
    char *h = *(char **)(p + 0x3c);

    return *(long *)(h + p) == 0x4c50;
}