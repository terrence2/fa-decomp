// w44G @ 0x4a31e0 (rva 0xa31e0, 80 B, unnamed, __cdecl void(), fpo).
// Socket-list reset: zero three counters from the esi-held loop counter,
// then walk a 0x32-stride table at sl+0x424 calling $FA$_t_4a32b0 on
// entries with a live flag byte at +0x18; count reloaded [sl] each pass.
// Real-C attempt v2 (v1 was byte-identical except FA increments esi
// BEFORE add edi,0x32 — statement order swapped to match).
extern unsigned char w44G_sl[];      /* ?socket_list@@3USOCKET_STATE_LIST@@A */
extern void __cdecl w44G_close_one(unsigned char *s);
void w44G_a31e0_q(void)
{
    long i;
    unsigned char *p;
    long n;

    i = 0;
    p = (unsigned char *)&w44G_sl[0x424];
    n = *(long *)&w44G_sl[0];
    *(long *)&w44G_sl[0x210] = i;
    *(long *)&w44G_sl[8] = i;
    *(long *)&w44G_sl[0x10c] = i;
    if (n > i) {
        do {
            if (p[0x18])
                w44G_close_one(p);
            i++;
            p += 0x32;
        } while (i < *(long *)&w44G_sl[0]);
    }
}