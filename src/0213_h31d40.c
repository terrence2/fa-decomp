// $FA$_t_431d40 @ rva 0x31d40 (46 B code; tail 8bff) — Rand dispatch: walk
// the item array at [ecx] until NULL, then call the twin (0x432140) with
// list[(short)Rand(n)]. FA: 56 / 8b 01 / 8b f1 / 33 c9 / 3b c1 / 74 0d /
// walker loop (8b c6 8b 50 04 83 c0 04 41 85 d2 75 f5) / e8 Rand /
// 0f bf c0 movsx / 8b 0c 86 / 51 / e8 twin / 83 c4 04 / 5e / c3
extern long __fastcall Rand(int n);
extern void w32d_twn(void *p);

typedef struct { void *v[64]; } LS;

void __fastcall w32d_randsel(LS *ls)
{
    int n = 0;
    while (ls->v[n]) n++;
    w32d_twn(ls->v[(short)Rand(n)]);
}