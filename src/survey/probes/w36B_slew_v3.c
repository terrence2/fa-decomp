/* w36B v1: ?ShowSlewObj@@YAXXZ rva 0x903e0 (96 B).
 * void __cdecl ShowSlewObj(void).  FA: 66 a1 16-B truncating load of
 * _slewId (4-B global), test ax, je shared tail; lea ecx,&loc;
 * and eax,0xffff (zero-extend); 8b 04 85 sib [eax*4+_objPtrs]; +0x11;
 * GRTo2d@8(objPtrs[i]+0x11, &loc) push ecx first; test/jl shared tail;
 * mov ecx,0xf G_SetColor@4 (fastcall ecx); G_Box@16: right-to-left pushes
 * 0x14 (p4), 0x14 (p3), loc[1]-10 (p2), loc[0]-10 (p1); add esp,4; ret.
 */
extern unsigned int slewId;
extern char *objPtrs[];
extern int __stdcall GRTo2d(void *a, short *b);
extern void __fastcall G_SetColor(int c);
extern void __stdcall G_Box(int a, int b, int c, int d);

void __cdecl w36bShowSlew(void)
{
    unsigned short s;
    short loc[2];
    s = (unsigned short)slewId;
    if (!s) return;
    if (GRTo2d(objPtrs[s] + 0x11, loc) < 0) return;
    G_SetColor(0xf);
    G_Box(loc[0] - 10, loc[1] - 10, 20, 20);
}