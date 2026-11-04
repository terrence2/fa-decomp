extern void __fastcall MMPushAllocId(int id);
extern void *__fastcall MMAllocPtr(int cb, int id);
extern void __fastcall MMPopAllocId(void);
extern unsigned long w32e_gt;

void *w32e_dllistinit_v1(unsigned short x)
{
    unsigned long *q;
    int i;
    MMPushAllocId(0x11);
    q = (unsigned long *)MMAllocPtr(0x24, 0);
    MMPopAllocId();
    for (i = 0; i < 9; i++)
        q[i] = 0;
    *(unsigned long *)((char *)q + 0x20) = w32e_gt;
    *(unsigned short *)((char *)q + 0x1a) = x;
    w32e_gt = (unsigned long)q;
    return (void *)q;
}