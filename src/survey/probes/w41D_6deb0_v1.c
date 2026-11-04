/* w41D 0x6deb0 (64 B, tail 8d642400+8da42400000000) — MP serial drain:
 * loop { r = MP_PeekByte(h); if (r) break; MP_Read(h, buf+3, 1); }
 * if (r == -1) return 0; return r.  fastcall (h param in ecx -> esi),
 * buf[4] local; the lea targets esp+7 (&buf[3]) computed pre-push.
 * Calls: MP_PeekByte = call mem (ff 15, w36F_ralloc proof), MP_Read =
 * ecx-held fnptr (call ecx) with the [MP_Read] load between the call
 * return and the test/jne (hoist question — v2 has the explicit rd copy).
 */
extern long (*MP_PeekByte)(long);
extern long (*MP_Read)(long, unsigned char *, long);

char __fastcall w41D_6deb0(long h)
{
    unsigned char buf[4];
    long r;
    while ((r = MP_PeekByte(h)) == 0)
        MP_Read(h, buf + 3, 1);
    if (r == -1)
        return 0;
    return (char)r;
}