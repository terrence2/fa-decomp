// w43G chunk rva 0xdde00 (85 B): binary-search a name table by _stricmp, return ushort id (ax).
// FA: saves ebx/esi/edi/ebp; ebx=0x63 (hi), edi=0 (lo), esi=param s; do-loop: mid(ebp) = (lo+hi)/2
//   (lea eax,[edi+ebx], cdq, sub, sar); push [__adbgmsg+0x60 + mid*8](entry name), push s,
//   call _stricmp; if 0 -> return word [ebp*8 + __adbgmsg+0x64]; if r<0: ebx=mid; else edi=mid;
//   loop while lo-hi != -1; fail: xor ax,ax; two full pop-bands (0x40 fail / 0x50 hit).
extern long __cdecl W43G_stricmp(char *a, char *b);

typedef struct {
    char *nm;
    short id;
    short pad;
} W43G_ENT;

extern W43G_ENT w43G_tab[];

unsigned short w43G_dde00_q(char *s)
{
    long lo, hi, mid;
    long r;

    hi = 0x63;
    lo = 0;
    do {
        mid = (lo + hi) / 2;
        r = W43G_stricmp(s, w43G_tab[mid].nm);
        if (r == 0)
            return (unsigned short)w43G_tab[mid].id;
        if (r >= 0)
            lo = mid;
        else
            hi = mid;
    } while (lo - hi != -1);
    return 0;
}
