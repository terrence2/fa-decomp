// _DrawLight320 @ rva 0x8aea0 — lock, pull light fields as 16/8-bit regs keeping
// high reg halves, sub-call with (v,w,b) pushed as dwords, tail-jmp unlock
// (probe w11b_04, byte-exact; ushort locals give the mov dx/ax forms and the
// void call as last statement gives FA's e9 tail)
extern void __stdcall dlLock_(void);
extern void __stdcall dlSub_(unsigned short v, unsigned short w, unsigned char b);
extern void __stdcall dlUnlock_(void);
void DrawLight320_q(void *o)
{
    unsigned short w;
    unsigned char b;
    unsigned short v;
    dlLock_();
    w = *(unsigned short *)((char *)o + 0xc);
    b = *(unsigned char *)((char *)o + 0x16);
    v = *(unsigned short *)((char *)o + 0xa);
    dlSub_(v, w, b);
    dlUnlock_();
}