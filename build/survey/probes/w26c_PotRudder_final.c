// ?PotRudder@@YAGFG@Z @ rva 0x17c60 = 98144, 48 B (cdecl; mangle YAGFG@Z =
//   unsigned short return, params (short, unsigned short); switch p1:
//   case 2 -> NormalizeStick(0,0,0,rudder) then return 0 (FA's body1 ends
//   xor ax,ax after the call); case 3 -> return p2 (16-bit stack load);
//   default -> 0; lea ecx,[ecx] pad).
// v4 (EXACT recipe): mangle-correct param types short/unsigned short.
extern unsigned char w26_rudder[]; /* map _w26_rudder=_rudder */
extern void __fastcall NormalizeStickQ(unsigned int a, unsigned int b,
                                       unsigned int *c1, void *c2); /* map @NormalizeStickQ@16=@NormalizeStick@16 */

unsigned short w26c_PotRudder_q(short p1, unsigned short p2)
{
    int c = p1;
    switch (c) {
    case 2:
        NormalizeStickQ(0, 0, 0, (void *)w26_rudder);
        return 0;
    case 3:
        return p2;
    default:
        return 0;
    }
}