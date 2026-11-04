/* 0x2770 (96 B) - unnamed: three fully separate return paths, each with its
   own triple store into *(p+0x176) (FA shows three copies of the
   [c+0x1c]/[c+0x14]/[c+0x18] store run with zeroed eax; CL CSEs them into
   one block, so spell independent bodies) and its own pop ebx/ret.
   Path A: *(p+0x112) > 1 -> [c+0x1c]=1 (c7 imm), zeros in eax.
   Path C (fall-through, *(p+0x10a)-1 > *(p+0x76)): [c+0x1c]=[r+0xc].
   Path B (unsigned <=): [c+0x1c]=[r+0x46]. r=*(p+0x116), b=*(p+0x76). */
long w43c_2770q(char *p)
{
    long *c;
    long v;
    unsigned long w, b, r;
    c = *(long **)(p + 0x176);
    v = *(long *)(p + 0x112);
    if (v > 1) {
        c[7] = 1;
        c[5] = 0;
        c[6] = 0;
        return 0;
    }
    w = *(unsigned long *)(p + 0x10a);
    b = *(unsigned long *)(p + 0x76);
    r = *(unsigned long *)(p + 0x116);
    if (w - 1 > b) {
        c[7] = *(long *)(r + 0xc);
        c[5] = 0;
        c[6] = 0;
        return 0;
    }
    c[7] = *(long *)(r + 0x46);
    c[5] = 0;
    c[6] = 0;
    return 0;
}