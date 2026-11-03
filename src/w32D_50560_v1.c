// $FA$_t_450560 @ rva 0x50560 (46 B code; tail 8bff) — twin of 0x31d40:
// walk list[] (this=ecx) until NULL, call twin (0x4508a0) with
// list[(short)Rand(n)].
extern long __fastcall Rand(int n);
extern void w32d_twn(void *p);

typedef struct { void *v[64]; } LS;

void __fastcall w32d_randsel2(LS *ls)
{
    int n = 0;
    while (ls->v[n]) n++;
    w32d_twn(ls->v[(short)Rand(n)]);
}