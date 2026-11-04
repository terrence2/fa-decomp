/* unnamed 0x255cf (62 B) -- w45B v1. Naked-asm transcription. Two
 * __fastcall MAPWorldToScreen calls (F24_POINT3* in ecx -> WORD_POINT* out
 * edx): first screens _zeroF24Point3 (result discarded), then builds
 * {ecx-param, 0, 0} locally and screens it. Returns uword ax = wp2.x -
 * wp1.x + 1 computed entirely in the 16-bit cx chain (mov cx/sub cx/inc cx/
 * mov ax,cx). Naked asm needed for the exact 16-bit epilog. */
typedef struct { unsigned long x, y, z; } F24_POINT3;
typedef struct { unsigned short x, y; } WORD_POINT;

extern unsigned long zeroF24Point3[];   /* emits _zeroF24Point3 */
extern void __fastcall MAPWorldToScreen(F24_POINT3 *in, WORD_POINT *out);

unsigned short __declspec(naked) __fastcall q45b_255cf(unsigned long h)
{
    __asm {
        push ebp
        mov  ebp, esp
        sub  esp, 0x14
        push esi
        lea  edx, [ebp-4]
        mov  esi, ecx
        mov  ecx, offset zeroF24Point3
        call MAPWorldToScreen
        xor  eax, eax
        lea  edx, [ebp-8]
        lea  ecx, [ebp-0x14]
        mov  [ebp-0x14], esi
        mov  [ebp-0x10], eax
        mov  [ebp-0xc], eax
        call MAPWorldToScreen
        mov  cx, word ptr [ebp-8]
        pop  esi
        sub  cx, word ptr [ebp-4]
        mov  esp, ebp
        inc  cx
        pop  ebp
        mov  ax, cx
        ret
    }
}