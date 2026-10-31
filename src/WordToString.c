/* WordToString — pilot 3 (chunk @ rva 0x11780, size 0x10, pure fastcall
 * thunk; FPO cdwLocals=0 cbParams? rec=80170100100000000000000000000000).
 *
 * FA asm:
 *   push 0x20; push -1; push edx; push ecx; call _DoWordToString@16; ret
 * FPO: offStart=0x11780 cbProcSize=0x10 cdwLocals=0 cbParams=0 flags=00 00
 * (tail pad 8d 6424 00 to 0x10)
 */
extern int __stdcall DoWordToString(int p1, int p2, int p3, int p4);

int __fastcall WordToString(int a, int b)
{
    return DoWordToString(a, b, -1, 0x20);
}