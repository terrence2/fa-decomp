// $FA$_t_4322f0 @ rva 0x322f0 (33 B code; census tail 15 B) — init loop:
// this(ecx) row table: dword0=0, then 10 rows of 18 B: dword -1 at p,
// byte 0 at old p+4. FA: c7 01 / 83 c1 04 / b8 0a / 33 d2 / loop: c7 01 /
// 83 c1 12 / 48 / 90 / 88 51 f2 / 75 f0 / c3
typedef struct { int hdr; char rows[10][18]; } SI;

void __fastcall w32d_init(SI *s)
{
    char *p;
    int i;
    s->hdr = 0;
    p = (char *)s + 4;
    i = 10;
    do {
        *(int *)p = -1;
        p += 18;
        *(p - 14) = 0;
    } while (--i);
}