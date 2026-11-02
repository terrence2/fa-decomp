extern void __fastcall GetCurObj(int id);
extern void __fastcall PutCurObj(void);
extern void __stdcall WPSetupCurrent(short v);
extern unsigned char curThing[];
extern unsigned short currentTime;
void __stdcall WPSetWaypoints(int id, int n)
{
    int f;
    GetCurObj(id);
    *(long *)(curThing + 0xe4) = n;
    f = n + 0x44;
    *(long *)(curThing + 0xe8) = f;
    WPSetupCurrent((short)(currentTime ? 2 : 0));
}