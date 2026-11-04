// @MMReallocHandle@8 @ rva 0x35b90 (220048 DEC; off 216976) (112 B) — EXACT
// winner (probe w24c_MMReallocHandle_v2.c). Pure CL C + 3 rel32 call maps,
// no byte patches. 0x6e body byte-identical + census tail 8bff (2 B).
//
// FA asm highlights: fastcall @8 (ecx=h, edx=size); flags staged as a
// 16-bit value: `66 8b 51 10` mov dx,[ecx+0x10] / `66 81 e2 ffbf` and
// dx,0xbfff (stale edx uppers ride the call — the 16-bit & 0xbfff on an
// unsigned short field is what makes CL emit the 66-and form); lazy push
// ebp AFTER the arg staging; call MMAllocHandle(esi=size,edx=flags); nd in
// ebp; min(srcSize,size) with SIGNED jl (7c 02) — h->size is a signed long
// in this struct; inline memcpy (shr edx,2... no: 8bc8/shr ecx,2/f3a5 +
// 8bc8/and ecx,3/f3a4) with edi=nd->data, esi=h->data; call
// MMInternalFree(edx=size,ecx=mem); field copies h->data/h->size from nd;
// ** `c7 45 08 00000000` nd->data = 0 BEFORE MMFreeHandle** — dis.py hides
// this zero-imm32 store; it is the single missing 7 B between v1 (0x67)
// and the EXACT 0x6e. mov ebp,ecx;call MMFreeHandle; mov al,1; pops; ret.
//
// C recipe: #include <string.h>; struct { char pad[8]; void *data; long
// size; unsigned short flags; } matches [0x8 data, 0xc size(dword), 0x10
// flags(word)]; mmcpy call with the signed-min ternary reproduces the jl
// idiom + rep movs inline; return unsigned char (xor al,al / mov al,1 tails);
// fastcall with all-register args -> plain c3 rets (no ret 8).
//
// Maps (obj FROM -> FA name):
//   @MMAllocHandle_q@8=@MMAllocHandle@8
//   @MMInternalFree_q@8=?MMInternalFree@@YIDPAXK@Z
//   @MMFreeHandle_q@4=@MMFreeHandle@4
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_MMReallocHandle_v2.obj 220048 \
//     build/survey/probes/w24c_MMReallocHandle_v2_fit.obj \
//     --map '@MMAllocHandle_q@8=@MMAllocHandle@8' \
//     --map '@MMInternalFree_q@8=?MMInternalFree@@YIDPAXK@Z' \
//     --map '@MMFreeHandle_q@4=@MMFreeHandle@4'
#include <string.h>

typedef struct { char pad[8]; void *data; long size; unsigned short flags; } MMH;

extern void * __fastcall MMAllocHandle_q(unsigned long size, unsigned short flags); /* @MMAllocHandle@8 */
extern void __fastcall MMInternalFree_q(void *mem, unsigned long size); /* ?MMInternalFree@@YIDPAXK@Z */
extern void __fastcall MMFreeHandle_q(MMH *h); /* @MMFreeHandle@4 */

unsigned char __fastcall MMReallocHandle_q(MMH *h, unsigned long size)
{
    MMH *nd = MMAllocHandle_q(size, h->flags & 0xbfff);
    if (nd == 0)
        return 0;
    memcpy(nd->data, h->data, h->size < (long)size ? h->size : (long)size);
    MMInternalFree_q(h->data, (unsigned long)h->size);
    h->data = nd->data;
    h->size = nd->size;
    nd->data = 0;
    MMFreeHandle_q(nd);
    return 1;
}
