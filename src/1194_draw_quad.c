/* w45F draw_quad @ 0x4d2de8 (88 B, gap chunk) — v1 husk for full-body
 * transplant (rep movs WORD x3 shape defeats plain-C memcpy expansion).
 * FA: 9-byte head (mov WORD [sqrt_table+0x1044],4) elided by dis.py;
 * 3 memcpys (2x rep movsd, 1x rep movs WORD), a0/a2 byte and a1/a3 dword
 * singles across sqrt_table+0x102c/0x102e -> +0x1064/0x1065, rep movsd,
 * call draw_nt, c3 90.
 * patch: 0x0,0xff,<88 FA bytes, 11 abs dwords + rel disp zeroed>
 *   + newsites 0x3..0x46 (6), 0x52 (20=REL32, disp START; e8 at 0x51). */
void w45F_drawq(void)
{
    return;
}