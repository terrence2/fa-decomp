/* w31H_92360 v1: FA bytes (rva 0x92360, 18 B code + 14 B pad): mov eax,[esp+4];
   mov BYTE PTR [eax+0x185],1; mov DWORD PTR [eax],0; ret. dis.py elided the
   7-B byte store — verified against raw FA. cdecl, 1 param. */
void w31h_92360(void *p)
{
    *(unsigned char *)((char *)p + 0x185) = 1;
    *(long *)p = 0;
}