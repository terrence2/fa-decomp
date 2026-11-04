/* rva 0x21ff3 (59 B) - world->screen transform; FA: movsx esi,[dMS+0xc] word loads */
extern volatile short desiredMapS[8];
extern volatile long mapScale;
extern volatile long worldCenter[4];

void __fastcall w43A_21ff3(short *in, long *out)
{
    out[0] = ((long)in[0] - (long)desiredMapS[3]) * mapScale + worldCenter[0];
    out[2] = ((long)desiredMapS[4] - (long)in[1]) * mapScale + worldCenter[2];
}
