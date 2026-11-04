/* wave-40C probe v1: unnamed 0x13e00 (48 B) - gun-selection step fn */
extern int w40c_snX;    /* ?selectNextMissile@@3JA+0x4 (VA 0x51e4d4) */
extern int w40c_lgbX;   /* ?lastGunButton@@3DA+0x8   (VA 0x51e4cc) */

char w40x_step13e00(unsigned short v)
{
    if (w40c_lgbX > w40c_snX) {
        *(unsigned short *)w40c_snX = v;
        w40c_snX = w40c_snX + 2;
        return 1;
    }
    return 0;
}