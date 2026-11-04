/* 0x6f960 ?MPGraphicAddCrater@@YIXPAUF24_POINT3@@J@Z 0x50
   FA: lea esi,&m.x BEFORE loads; j-store via [esp+0x15]; x/y loads, then z
   load, pushes interleaved (1, 0x11), stores x/y/z via esi walker,
   &m lea, t store, push -1, call. */
#pragma pack(push, 1)
typedef struct { long x, y, z; } F24PT3;
typedef struct { unsigned char t; F24PT3 pos; long j; } F24MSG;
#pragma pack(pop)
extern unsigned long numComputers;
extern void __stdcall w43D_snd(long id, void *msg, long size, long flag);

void __fastcall w43D_crater(void *p, long j)
{
    F24MSG m;
    unsigned long *w;
    if (numComputers == 1)
        return;
    m.j = j;
    w = (unsigned long *)((char *)&m + 1);
    w[0] = *(unsigned long *)p;
    w[1] = *(unsigned long *)((char *)p + 4);
    w[2] = *(unsigned long *)((char *)p + 8);
    m.t = 0x1b;
    w43D_snd(-1, &m, 0x11, 1);
}
