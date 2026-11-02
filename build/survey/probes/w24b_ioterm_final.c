// __ioterm @ rva 0xdc120 (901408) — 85 B code, no pad. CL C + 5 patches — EXACT.
// Source probes w24b_ioterm_v1.c..v3.c (probes/).
//
// Shape: CRT io-table shutdown. Iterates the io-block pointer array from
// __crtheap+4 (FA imm32 0x588c70) to &__nhandle (0x588d70), one pointer per
// step (add esi,4). Per non-NULL block t: if t+0x480 > t walk the 0x24-byte
// entry array DeleteCriticalSection-ing each entry with a non-zero +8 field
// (CS taken at +0xc); then free(*q) via _free (chunk 0xd8130). ebp is a
// zero-cached compare register (xor ebp,ebp; cmp [ebx+8],ebp), hoisted out
// of the inner loop; DeleteCriticalSection's IAT slot content is loaded
// once into edi before everything but the block loop (mov edi,[imp]);
// the block cursor re-reads *q each inner iteration.
//
// C shape levers (w3, decisive): declare q BEFORE dcs — CL4.2 assigns
// saved-reg slots in declaration order, so q-first gets esi (and dcs edi),
// which also makes CL emit FA's exact prolog split
//   53 56 57 be+imm(q=&__crtheap+4) 55 8b3d+imp(dcs) — 15 B, matches FPO cbProlog 0x0f
// and the lea [ebx+0x480]/cmp eax,ebx pair with no extra mov. The z=0
// register local did NOT reproduce FA's cmp [ebx+8],ebp (CL folds to
// mov eax,[ebx+8]/test) — patched.
//
// Patches (state toolchain-diff, provenance 'patch 0x14-0x50: fa/CL codegen
// delta — CL folds the +8 zero test to mov/test (FA: cmp [ebx+8],ebp) and
// four jcc disp bytes disagree with the post-FOLD layout; offsets from
// layout.json chunk 0xdc120, probe w24b_ioterm_v3'):
//   --patch '33,5,396b08'   zero-check: 8b4308 85c0 (mov eax,[ebx+8]/test)
//                           -> 396b08 (cmp [ebx+8],ebp); -2 bytes; every
//                           later byte/jcc disp shifts -2
//   --patch '20,1,30'       je +0x32 -> +0x30 (t==NULL skips to add esi,4)
//   --patch '30,1,1b'       jbe +0x1d -> +0x1b (size-fail -> free block)
//   --patch '57,1,e7'       ja -0x1b -> -0x19 (inner loop back to the cmp)
//   --patch '79,1,bf'       jb -0x43 -> -0x41 (block loop back to 8b1e)
//
// Maps:
//   __qStart  = __crtheap+4   (be imm32; DIR32, addend 4 baked; FA content
//                              0x588c70 = __crtheap+4)
//   __qEnd    = __nhandle     (cmp imm32; DIR32; FA content 0x588d70)
//   __dcsIAT  = __imp__DeleteCriticalSection  (8b3d moffs; slot loaded once,
//                              ff d7 call through edi in the loop)
//   __frea    = _free         (rel32 call to chunk 0xd8130)
// Externals after fit: __crtheap, __imp__DeleteCriticalSection, _free,
// __nhandle (all in FA universe). Defines __ioterm. Tail: none (pad 0).
typedef void (__stdcall *PCSFN)(void *);
extern PCSFN _dcsIAT;        /* __imp__DeleteCriticalSection slot content */
extern void _frea(void *q);  /* chunk 0xd8130 */
extern char _qStart;         /* __crtheap+4  (imm32 in code) */
extern char _qEnd;           /* __nhandle    (imm32 in code) */

void __cdecl __ioterm_q(void)
{
    void **q;
    PCSFN dcs;
    unsigned char *c;
    void *t;
    unsigned long z;

    q = (void **)&_qStart;
    dcs = _dcsIAT;
    do {
        t = *q;
        if (t != 0) {
            c = (unsigned char *)t;
            z = 0;
            if ((unsigned char *)((unsigned long)c + 0x480) > (unsigned char *)t) {
                do {
                    if (((unsigned long *)c)[2] != z)
                        dcs((void *)(c + 0xc));
                    c += 0x24;
                } while ((unsigned long)*(unsigned long **)q + 0x480
                         > (unsigned long)c);
            }
            _frea((void *)*(void **)q);
        }
        q += 1;
    } while (q < (void **)&_qEnd);
}
