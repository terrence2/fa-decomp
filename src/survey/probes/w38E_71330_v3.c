/* MPSetFuel v3: drop staging local — direct ushort return store, direct
 * field RHS store, no extended id staging (FA pushes esi raw — patched). */
extern unsigned long numComputers;
extern unsigned long curThing1fc;   /* _curThing+0x1fc */
extern void __stdcall PushCurObj(unsigned long);
extern void __stdcall PopCurObj(void);
extern unsigned short __fastcall OBJAlias(unsigned short, unsigned long);
extern void __fastcall w38e_flush(unsigned char);
extern long __stdcall w38e_46b260(long, unsigned char *, long, long);

void __fastcall MPSetFuel(unsigned short id)
{
    unsigned char t[8];
    unsigned short v;
    if (numComputers == 1)
        return;
    v = (unsigned short)id;
    PushCurObj((unsigned long)id);
    t[0] = 0x47;
    *(unsigned short *)(t + 1) = OBJAlias(v, 1);
    *(unsigned long *)(t + 3) = curThing1fc;
    w38e_46b260(-1, t, 7, 1);
    w38e_flush(0);
    PopCurObj();
}