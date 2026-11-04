/* w44C c13a0 — v2: keep 0x7fff in EAX through compare+store (cmp ax,[mem] vs
 * FA's mem-vs-ax; expected 1-B 39/3b direction swap), a1-load word, xor+cx
 * zero-extend for the imul, add ax,[mem] final. */
extern char curThingType[], curThing[], currentT[];
extern short __fastcall Rand(long);

void w44c_4c13a0(void)
{
    long v, d, wl;
    unsigned short t;
    v = 0x7fff;
    if (*(unsigned short *)(curThingType + 0xb1) == v) {
        *(unsigned short *)(curThing + 0x128) = v;
        return;
    }
    d = 0x64;
    v = Rand(0x42);
    v = v + 0x42;
    wl = (unsigned short)*(unsigned short *)(curThingType + 0xb1);
    v = v * wl / d;
    t = *(unsigned short *)currentT;
    *(unsigned short *)(curThing + 0x128) = (unsigned short)(v + t);
}