// ?FindStreamerDef@@YIPAUSTREAMER_DEF@@PAE@Z @ rva 0x9dd90 (32 B) — fastcall
//   unsigned char *p; p += 0xe; match word 0xf2 steps p by 4; match word
//   0xce returns p+2 (lea eax,[ecx+2]); else 0.
void *__fastcall FindStreamerDef_q(unsigned char *p)
{
    p += 0xe;
    if (*(unsigned short *)p == 0xf2)
        p += 4;
    if (*(unsigned short *)p == 0xce)
        return (void *)((char *)p + 2);
    return 0;
}