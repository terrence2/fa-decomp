/* _GRPLeaderLanding@0 rva 0x5ec50, twin of 0x5df20 with GRPPart/GRPLeader callees.
 * calls: _GRPPart@12 (0x5ea70), @GRPLeader@4 (0x5e990), _PushCurObj@4,
 * _OnTheGround@0, _PopCurObj@0 — all layout publics, no $FA$_t TOs. */
extern char __stdcall GRPPart(short, int *, int *);
extern long __fastcall GRPLeader(int);
extern void __stdcall PushCurObj(long);
extern char __stdcall OnTheGround(void);
extern void __stdcall PopCurObj(void);
extern unsigned short curId;
extern char w38d_ctX[];

char __stdcall GRPLeaderLanding(void)
{
    char fl[4];
    int buf;
    short id;
    unsigned char ch, b;

    id = curId;
    GRPPart(id, &buf, 0);
    PushCurObj(GRPLeader(buf));
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