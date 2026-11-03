/* FA chunk @APAdd@4 rva 0xb6ba0 (112 B) — wave 33 batch E probe v1.
   Fastcall: arg (source 0x134-B airport record) in ecx. Replaces the first
   stored airport whose +0xe6 word equals the arg's, else appends a copy at
   airports[numAirports] when the store is under the 40 cap. FA computes the
   append slot (idx * 0x134 via the 9x/19x/77x lea chain) up front. */
struct AP { char _0[0xe6]; short w; char _e8[0x134 - 0xe8]; };
extern short numAirports;         /* 0x582970, short global */
extern struct AP airports[40];    /* 0x582998 */

char __fastcall APAdd(struct AP *s)
{
    struct AP *dst;
    struct AP *e;
    short w;
    dst = &airports[numAirports];
    e = airports;
    w = s->w;
    if (e < dst)
    {
        for (;;)
        {
            if (e->w == w)
                goto found;
            e++;
            if (!(e < dst))
                break;
        }
    }
    if (numAirports < 40)
    {
        numAirports++;
        *dst = *s;
        return 1;
    }
    return 0;
found:
    *e = *s;
    return 1;
}