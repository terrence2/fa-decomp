/* FA chunk @APAdd@4 rva 0xb6ba0 (112 B) — wave 33 batch E probe v2.
   v2: the found path shares the struct copy block — FA's je lands past the
   mov edi,eax that only the append path executes. dst is precomputed
   (idx*0x134 lea chain) before the scan; e is the walker. FA keeps the arg
   in ecx all the way into the rep movsd (mov esi,ecx at the copy block). */
struct AP { char _0[0xe6]; short w; char _e8[0x134 - 0xe8]; };
extern short numAirports;         /* 0x582970, short global */
extern struct AP airports[40];    /* 0x582998 */

char __fastcall APAdd(struct AP *s)
{
    struct AP *dst;
    struct AP *e;
    dst = &airports[numAirports];
    e = airports;
    if (e < dst)
    {
        for (;;)
        {
            if (e->w == s->w)
                goto copy;
            e++;
            if (!(e < dst))
                break;
        }
    }
    if (numAirports < 40)
    {
        numAirports++;
        e = dst;
        goto copy;
    }
    return 0;
copy:
    *e = *s;
    return 1;
}