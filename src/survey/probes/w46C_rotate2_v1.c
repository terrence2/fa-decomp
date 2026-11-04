// Wave 46 batch C entry 9: _Rotate2@8 @ rva 797188 (0xc2a04), 120 B.
// stdcall (ret 8, ebp frame): loads arg2 (short angle) into ebx, calls the
// register-ABI helper sincos (angle in bx; returns sin in ax, cos in ebx --
// w33F notes), stores ax*/*bx sign-extended to _curThingType+0x32c/0x330,
// then rotates (*p, p[+8]) fixed-point (>>15 shrd) through sin/cos and
// stores back to *p / p[+8]. Globals are interior to the _curThingType
// data chunk. 1-B tail pad 90 (code 0x77).
extern long w46c_g1;   /* _curThingType+0x32c (sin)   */
extern long w46c_g2;   /* _curThingType+0x330 (cos)   */
extern long w46c_g3;   /* _curThingType+0x338         */
extern void sincosHelper(void);   /* public 'sincos'  */

void __declspec(naked) Rotate2_q(void)
{
    __asm {
        push ebp
        mov  ebp, esp
        push ebx
        push ebp
        movsx ebx, word ptr [ebp+0xc]
        call sincosHelper
        movsx eax, ax
        movsx ebx, bx
        mov  w46c_g1, eax
        mov  w46c_g2, ebx
        pop  ebp
        mov  ebp, dword ptr [ebp+8]
        mov  ebx, dword ptr [ebp]
        mov  eax, dword ptr [ebp+8]
        mov  w46c_g3, eax
        mov  eax, w46c_g3
        imul w46c_g1
        shrd eax, edx, 0xf
        mov  ecx, eax
        mov  eax, ebx
        imul w46c_g2
        shrd eax, edx, 0xf
        add  eax, ecx
        mov  dword ptr [ebp], eax
        mov  eax, w46c_g3
        imul w46c_g2
        shrd eax, edx, 0xf
        mov  ecx, eax
        mov  eax, ebx
        imul w46c_g1
        shrd eax, edx, 0xf
        sub  ecx, eax
        mov  dword ptr [ebp+8], ecx
        pop  ebx
        pop  ebp
        ret  8
    }
}