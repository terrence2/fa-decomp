// _HARDLoadAll@0 @ rva 0x52330 (336688 DEC; off 333616) (80 B) — EXACT
// winner (probe w24c_HARDLoadAll_v2.c). Pure CL C, NO patches.
//
// FA asm (0x41 body + census tail 8d642400 x2 + 8da42400000000 = 15 B):
//   sub esp,4 (out-slot p) / mov al,ds:[_curThingType+0xb5] (byte load,
//   a0 moffs) / push esi / xor esi,esi (i=0, unconditional before guard) /
//   test al,al / je epilogue / loop: lea eax,[esp+4] (=&p) / push eax /
//   push 0 / push esi (i) / call _HARDPtrs@12 / mov eax,[esp+4] (reload p
//   after call) / mov eax,[eax+0x10] / test eax,eax / je skip / push 0 /
//   push eax / push esi / call _HARDLoad@12 / skip: inc esi / xor eax,eax /
//   mov al,ds:[_curThingType+0xb5] (back-test re-read, xor+mov-al widening
//   NOT movzx) / cmp eax,esi / jg loop; pop esi / add esp,4 / ret.
//
// C recipe:
//   - The back-test widening is the steer: declare the byte as a SCALAR
//     `extern unsigned char` (mapped _curThingTypeB5=_curThingType+0xb5) —
//     CL then emits FA's xor eax,eax + mov al,moffs for the re-read. With
//     the char[]-array spelling (curThingTypeQ[0xb5] probe v1) CL emitted
//     movzx (0fbe) AND hoisted it ahead of the inc esi.
//   - do-while inside `if (c)` with the global `c > i` compare re-reading
//     the global after i++ (calls in the body force the reload).
//   - `void *p;` local; HARDPtrs_q(i, 0, &p) stages &p with lea eax,[esp+4]
//     and pushes right-to-left (&p, 0, i).
//   - ld = *(unsigned long *)((char *)p + 0x10); if (ld) HARDLoad_q(i, ld, 0)
//     reproduces test/jne + push 0/push eax/push esi.
//   - void __stdcall for the @0 suffix.
//
// Maps (obj FROM -> FA name): _curThingTypeB5=_curThingType+0xb5,
// _HARDPtrs_q@12=_HARDPtrs@12, _HARDLoad_q@12=_HARDLoad@12.
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_HARDLoadAll_v2.obj 336688 \
//     build/survey/probes/w24c_HARDLoadAll_v2_fit.obj \
//     --map '_curThingTypeB5=_curThingType+0xb5' \
//     --map '_HARDPtrs_q@12=_HARDPtrs@12' \
//     --map '_HARDLoad_q@12=_HARDLoad@12'
extern unsigned char curThingTypeB5;  /* _curThingType+0xb5 */
extern void __stdcall HARDPtrs_q(long t, unsigned long z, void **out); /* _HARDPtrs@12 */
extern void __stdcall HARDLoad_q(long t, unsigned long a, unsigned long b); /* _HARDLoad@12 */

void __stdcall HARDLoadAll_q(void)
{
    void *p;
    long i = 0;
    if (curThingTypeB5) {
        do {
            unsigned long ld;
            HARDPtrs_q(i, 0, &p);
            ld = *(unsigned long *)((char *)p + 0x10);
            if (ld)
                HARDLoad_q(i, ld, 0);
            i++;
        } while (curThingTypeB5 > i);
    }
}
