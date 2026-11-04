/* _WNGLeaderLanding@0 rva 0x5df20, 128 B (121 code + 7 tail 8d a4 24 00 00 00 00).
 * FA: mov cx,[curId] / sub esp,8 / lea eax,[esp+4] (&buf) / push ebx /
 * push 0 / push eax / push ecx / call _WNGPart@12 / mov ecx,[esp+8] (buf) /
 * call $FA$_t_45dc60 / push eax / call _PushCurObj@4 /
 * mov ebx,[curThing+1] / mov al,[curThing+0xe3] / and bl,1 /
 * cmp al,0x13 jb; cmp al,0x1e ja; fl=1 : fl=0 / call _OnTheGround@0 store fl2 /
 * call _PopCurObj@0 / test bl,bl je 0 / fl1 jne 1 / fl2 je 0 / 1: b0 01 */
extern char __stdcall WNGPart(short, int *, int *);
extern long __fastcall WNGLeader(int);
extern void __stdcall PushCurObj(long);
extern char __stdcall OnTheGround(void);
extern void __stdcall PopCurObj(void);
extern unsigned short curId;
extern char w38d_ctX[];

char __stdcall WNGLeaderLanding(void)
{
    char fl[4];
    int buf;
    short id;
    unsigned char ch, b;

    id = curId;
    WNGPart(id, &buf, 0);
    PushCurObj(WNGLeader(buf));
    b = *(long *)(w38d_ctX + 1) & 1;
    ch = w38d_ctX[0xe3];
    if (ch >= 0x13 && ch <= 0x1e)
        fl[3] = 1;
    else
        fl[3] = 0;
    fl[2] = OnTheGround();
    PopCurObj();
    return b && (fl[3] || fl[2]);
}