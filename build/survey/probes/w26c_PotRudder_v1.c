// ?PotRudder@@YAGFG@Z @ rva 0x17c60 = 97376, 48 B (cdecl short,ushort; FA:
//   movsx eax,[esp+4]; cmp eax,2 je; cmp eax,3 je; xor ax,ax ret // ==2:
//   push 0x54a030? no: push (addr _rudder); xor edx,edx; push 0; xor ecx,ecx;
//   call @NormalizeStick@16 (fastcall 4 args ecx,edx,c,d); xor ax,ax; ret //
//   ==3: mov ax,[esp+8]; ret).
extern unsigned char w26_rudder[]; /* map _w26_rudder=_rudder */
extern void __fastcall NormalizeStickQ(int a, int b, int c, void *d); /* map @NormalizeStickQ@16=@NormalizeStick@16 */

unsigned short __cdecl w26c_PotRudder_q(short p1, unsigned short p2)
{
    if (p1 == 2) {
        NormalizeStickQ(0, 0, 0, (void *)w26_rudder);
        return 0;
    }
    if (p1 == 3) return p2;
    return 0;
}