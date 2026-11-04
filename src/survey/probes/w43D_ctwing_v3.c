/* 0x64b20 CTEval_wingcombat 0x90 — v3: signed WNGWingmen out1 (7c jl fix)
 * + Dist args swapped in C (net_mung_name recipe: CL right-to-left then
 * reproduces FA's add/push order: 83c0 11 / 50 / 68 <curThing+0x11>).
 */
extern short serviceTicks[];
extern unsigned short curId;
extern unsigned char curThing[];
extern char __stdcall WNGPart(unsigned short id, unsigned long *out1, unsigned long out2);
extern char * __stdcall WNGWingmen(unsigned long id, long *out1);
extern unsigned char * __fastcall OBJGet(unsigned short id);
extern long __stdcall Dist(long a1, long a2);

long __cdecl CTEval_wingcombat(void)
{
    long s0, s1;
    unsigned short w;
    unsigned char *o;
    unsigned short idw;
    if (*(unsigned short *)(serviceTicks + 0x20) == 0)
        goto endfail;
    if (WNGPart(curId, &s0, 0) != 1)
        goto endfail;
    o = (unsigned char *)WNGWingmen(s0, &s1);
    if (s1 < 1)
        goto endfail;
    idw = *(unsigned short *)o;
    o = OBJGet(idw);
    if ((*(unsigned long *)((char *)o + 1) & 1) == 0)
        goto endfail;
    if (*(unsigned short *)((char *)o + 0xee) == *(unsigned short *)(serviceTicks + 0x20))
        goto ret8;
    if (*(unsigned char *)((char *)o + 0xe3) >= 0x20)
        goto endfail;
ret8:
    return Dist((long)(curThing + 0x11), (long)o + 0x11) >> 8;
endfail:
    return 0;
}