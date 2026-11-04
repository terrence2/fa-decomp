/* w42A_initmove_v1.c — FA chunk @InitScreenMove@4 rva 0x86c0 (VA 0x4086c0)
 *
 * fastcall short angle: push esi; eax=0x10000; mov si,cx;
 *   a3 [unitRight]=eax; xor ecx,ecx; push esi; push imm32 _unitRight;
 *   89 0d [unitRight+8]=ecx; 89 0d [unitUp]=ecx; a3 [unitUp+8]=eax;
 *   call _Rotate2@8; push esi; push imm32 _unitUp; call _Rotate2@8;
 *   movsx ecx,word[_grMode+6]; a1 [unitRight]; shl 8; +0x80; cdq; idiv ecx;
 *   a3 [unitRight]; a1 [unitUp]; shl 8; 5e pop esi; add 0x80; cdq;
 *   idiv ecx; a3 [unitUp]; ret; pad 8d9b00000000 (6 B).
 * _Rotate2@8 still stub (identity extern). unitRight 0x51d630 size 24,
 * unitUp 0x51d648 size 40, grMode 0x5535b0 (word at +6).
 */
extern char unitRight[];
extern char unitUp[];
extern char grMode[];
extern void __stdcall Rotate2(long *v, short a);

void __fastcall InitScreenMove(short angle)
{
    long y;
    long z;
    long d;
    short s;

    y = 0x10000;
    s = angle;
    *(long *)unitRight = y;
    z = 0;
    *(long *)(unitRight + 8) = z;
    *(long *)unitUp = z;
    *(long *)(unitUp + 8) = y;
    Rotate2((long *)unitRight, s);
    Rotate2((long *)unitUp, s);
    d = *(short *)(grMode + 6);
    *(long *)unitRight = ((*(long *)unitRight << 8) + 0x80) / d;
    *(long *)unitUp = ((*(long *)unitUp << 8) + 0x80) / d;
}