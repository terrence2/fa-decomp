/* w31F / _PLANESetFeetWet@0 @ rva 648496 (0x9e530) 80 B FPO/esp stdcall
 * FA: sub esp,0x4 (local 4B); mov cx,WORD[curId]; push 0x4(arg6);
 * lea eax,[esp+0x7](=&out[3]); push eax(arg5); push 0x0(arg4);
 * push 0x508749(=curThing+0x11)(arg3); push 0x508738(=curThing)(arg2);
 * push ecx(arg1=curId); call _T_Info@24;
 * mov cl,[esp+0x3]((char)out[3]); mov eax,ds:0x5088a7 (=*(long*)(curThing
 * +0x16f), a1 moffs); test cl,cl; je L2; or eax,0x8000000; add esp,0x4;
 * mov ds:0x5088a7,eax; ret /
 * L2: and eax,0xf7ffffff; add esp,0x4; mov ds:0x5088a7,eax; ret */
extern unsigned short curId;
extern char curThing[];
extern long __stdcall T_Info(short a, char *b, char *c, long d, long e,
                             int f);

void __stdcall PLANESetFeetWet(void)
{
    char out[4];
    unsigned long f;
    T_Info(curId, curThing, curThing + 0x11, 0, (long)(out + 3), 4);
    f = *(unsigned long *)(curThing + 0x16f);
    if (out[3])
        *(unsigned long *)(curThing + 0x16f) = f | 0x8000000;
    else
        *(unsigned long *)(curThing + 0x16f) = f & 0xf7ffffff;
}