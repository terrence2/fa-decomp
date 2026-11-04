/* w38F_ddec0_v2: unnamed @ rva 0xddec0 — 16-bit div/mod100+90 clamp, branch
 * shape, WORD table lookup tab[3*r] (map to __adbgmsg+0x630). */
extern unsigned short __cdecl _w38f_ext(unsigned short);
extern unsigned short w38f_tab[];

unsigned short _w38f_ddc(unsigned short v)
{
    unsigned short d = 100;
    unsigned short t, r;
    if (v > 100) {
        t = _w38f_ext(v);
        if (t != 0)
            return t;
    }
    r = v % d;
    if (r > 90)
        return 0;
    return w38f_tab[r * 3];
}