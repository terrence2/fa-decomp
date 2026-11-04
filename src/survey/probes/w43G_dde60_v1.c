// w43G chunk rva 0xdde60 (85 B): dde00 twin - binary-search a name table by _stricmp, ushort id in ax.
// FA: ebx=0x57 (hi); table reads at __adbgmsg+0x378 (name) / __adbgmsg+0x37c (id); rest identical to dde00.
extern long __cdecl W43G_stricmp(char *a, char *b);

typedef struct {
    char *nm;
    short id;
    short pad;
} W43G_ENT;

extern W43G_ENT w43G_tabB[];

unsigned short w43G_dde60_q(char *s)
{
    long lo, hi, mid;
    long r;

    hi = 0x57;
    lo = 0;
    do {
        mid = (lo + hi) / 2;
        r = W43G_stricmp(s, w43G_tabB[mid].nm);
        if (r == 0)
            return (unsigned short)w43G_tabB[mid].id;
        if (r >= 0)
            lo = mid;
        else
            hi = mid;
    } while (lo - hi != -1);
    return 0;
}
