// _GRSinCos@12 @ rva 0xd2048 (40 B, gap chunk) — stdcall sin/cos pair:
// prologue, save ebx/esi/edi, push ebp (arg), fetch the 16-bit angle,
// push ebp again, call sincos (chunk 0xca841: x87 table math, returns
// sin in AX / cos in BX), pop ebp, store AX->sin*, BX->cos*, epilogue,
// ret 12. The callee arg pushes are literal ebp pushes (asm-only
// register contract); naked.
extern void sincosHelper(void);

void __declspec(naked) GRSinCos(void)
{
    __asm {
        push ebp
        mov  ebp, esp
        push ebx
        push esi
        push edi
        push ebp
        mov  bx, word ptr [ebp+8]
        push ebp
        call sincosHelper
        pop  ebp
        mov  esi, dword ptr [ebp+0xc]
        mov  word ptr [esi], ax
        mov  esi, dword ptr [ebp+0x10]
        mov  word ptr [esi], bx
        pop  ebp
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        ret  12
    }
}