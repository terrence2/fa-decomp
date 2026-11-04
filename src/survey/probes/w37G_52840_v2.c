/* _HARDUnrotatedHardPos@12 @ rva 0x52840 (128 B) v2: v1 spelling with the
   curThing+0xde exterior typed unsigned long (a1 moffs load, a8 test) */
extern unsigned long gamePrefs;     /* -> _gamePrefs */
extern unsigned long w37G_ctde;     /* -> _curThing+0xde (0x508816) */

void __stdcall HARDUnrotatedHardPos(void *hard, long *st, long *out)
{
    long x;
    unsigned char *obj;
    short w;
    long div;

    x = (long)*(short *)((char *)hard + 2) << 8;
    out[0] = x;
    x = (long)*(short *)((char *)hard + 4) << 8;
    out[1] = x;
    x = (long)*(short *)((char *)hard + 6) << 8;
    out[2] = x;
    if (*(unsigned char *)hard & 4) {
        obj = (unsigned char *)*st;
        if (obj != 0 && *(unsigned char *)obj == 7) div = obj[0xf0];
        else div = 1;
        w = *(short *)((char *)st + 4);
        if (((long)w / div) & 1) out[0] = -out[0];
        if (gamePrefs & 8) {
            if (w37G_ctde & 0x40) out[0] = -out[0];
        }
    }
}