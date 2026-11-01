// _CTEval_h @ rva 0x64890 (64 B) — heading of _curThing+0x1d (+0x5b) run
//   through the 16-bit UNSIGNED div chain (sub dx,dx / div cx = ushort /),
//   then FA's dead negative-guard: (short)q < 0 re-entry 0x167-q over 0x168
//   (360) wraps the quotient back — q can never reach 0x8000 for a 16-bit
//   dividend, but CL must still emit the branch.
extern char curThing[];
int CTEval_h_q(void)
{
    unsigned short w, q, t;
    w = *(unsigned short *)(curThing + 0x1d);
    w = w + 0x5b;
    q = w / 0xb6;
    if ((short)q < 0)
    {
        t = 0x167 - q;
        t = t / 0x168;
        t = t * 0x168;
        q = q + t;
    }
    return (short)q;
}