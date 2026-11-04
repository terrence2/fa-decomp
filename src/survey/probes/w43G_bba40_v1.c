// w43G chunk rva 0xbba40 (64 B): gap-anchor table-point setter.
// FA: esi = s; if (s->0x12 == 0) { eax = *(void**)(s+4); s->0x12 = (*(fn**)eax)(s,0,0x1c); }
//     t = s->0x12; eax = val; stores (t+8)=0x4bba80, (t+0xc)=0x4bbab0, (t+0x10)=0x4bbb00
//     c7 dwords w/ DIR32 (gap chunks still stubs, anchors $FA$_t_4bba80/...); (t+0x14)=val; ret.
// extern char arrays so the c7 imms carry genuine DIR32 fixups (map TOs = $FA$_t anchors).
typedef long (__cdecl * W43G_bba40_fp)(void *, long, long);

extern char w43G_jt0[];
extern char w43G_jt1[];
extern char w43G_jt2[];

long w43G_bba40_q(char *s, long val)
{
    if (*(long *)(s + 0x12) == 0) {
        *(long *)(s + 0x12) =
            (**(W43G_bba40_fp **)(s + 4)) (s, 0, 0x1c);
    }
    {
        long t = *(long *)(s + 0x12);
        *(char **)(t + 8) = w43G_jt0;
        *(char **)(t + 0xc) = w43G_jt1;
        *(char **)(t + 0x10) = w43G_jt2;
        *(long *)(t + 0x14) = val;
    }
    return val;
}