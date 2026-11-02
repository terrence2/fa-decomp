// ?PotRudder@@YAGFG@Z @ rva 0x17c60 = 48, 48 B (cdecl short, ushort ret;
//   FA: movsx eax,[esp+4] (32-bit ext); cmp eax,2; je body1; cmp eax,3;
//   je body2; xor ax,ax; ret; body1: push &rudder; xor edx; push 0; xor
//   ecx; call @NormalizeStick@16; xor ax,ax; ret; body2: mov ax,[esp+8];
//   ret. v2: int-extended switch with bodies at case labels).
extern void *w26_rudder; /* map _w26_rudder=_rudder */
extern void __fastcall NormalizeStickQ(int a, int b, int c, void *d); /* map @NormalizeStickQ@16=@NormalizeStick@16 */

unsigned short __cdecl w26c_PotRudder_q(short p1, unsigned short p2)
{
    int c = p1;
    switch (c) {
    case 2:
        NormalizeStickQ(0, 0, 0, (void *)w26_rudder);
        return 0;
    case 3:
        return p2;
    }
    return 0;
}