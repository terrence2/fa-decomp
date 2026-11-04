// w40G_79af0_v2 — CSE defeat: three distinct extern spellings of the same
// public (curThing/curThing2/curThing3, mapped to _curThing in fitobj) so
// CL cannot fold the three reads; each condition reads its own alias to
// keep CL's cmp/movsx forms on memory like FA.
extern char curThing[];
extern char curThing2[];
extern char curThing3[];

int w40g_joymap(void)
{
    long v;
    if (*(short *)(curThing + 0x1f) >= 0)
        return 0x100;
    if (*(short *)(curThing2 + 0x1f) < 0xe002)
        return 0;
    v = *(short *)(curThing3 + 0x1f);
    return ((v + 0x1ffe) << 8) / 0x1ffe;
}