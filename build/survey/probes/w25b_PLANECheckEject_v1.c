extern void __fastcall EJECTAdd(long c);
extern void __stdcall PLANESetEjectTime(int t);
extern unsigned char curThing[];
extern unsigned short currentT;
extern long thisComputer;
void __stdcall PLANECheckEject(void)
{
    if (*(unsigned short *)(curThing + 0x23c) <= currentT
        && *(unsigned char *)(curThing + 0x23e))
    {
        EJECTAdd(thisComputer);
        *(unsigned char *)(curThing + 0x23e) -= 1;
        PLANESetEjectTime(0);
    }
}