/* w45F switch-dispatch @ 0x4d9d90 (95 B, FPO 1 param fpo/esp) — v1
 * FA: v=[esp+4]; eax=v-0x3a4; if (eax>0x12) -> default (xor eax,0; ret);
 *   else cl=case-byte[idx]+eax*4 -> jump table (dwords at 0x4d9dc8);
 *   cases: 0->0x4d9db0 (eax=0x411), 4->0x4d9db6 (0x804), 17->0x4d9dbc
 *   (0x412), 18->0x4d9dc2 (0x404); jump/case tables inline in .text. */
unsigned long __cdecl w45F_d9d90(unsigned long v)
{
    switch (v - 0x3a4) {
    case 0:
        return 0x411;
    case 4:
        return 0x804;
    case 17:
        return 0x412;
    case 18:
        return 0x404;
    default:
        return 0;
    }
}