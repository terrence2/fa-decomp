// __set_sbh_threshold @ rva 0xddfd0 — round up to a paragraph, cap 0x780;
//   success-block written first with ret0 last (ja +0xb over it, d175)
extern char adbgmsg[];
int set_sbh_threshold_q(int n)
{
    unsigned long t = (n + 0xf) & ~0xf;
    if (t <= 0x780)
    {
        *(long *)(adbgmsg + 0x1074) = t;
        return 1;
    }
    return 0;
}
