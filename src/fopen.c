// _fopen @ rva 0xd3ff0 — forwarder: t4d3fb0(f, m, 0x40) (probe d91 exact).
extern int t4d3fb0(char *f, char *m, int fl);

int _fopen_q(char *f, char *m)
{
    return t4d3fb0(f, m, 0x40);
}
