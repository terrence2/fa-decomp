// @G_DrawYLR@4 @ rva 0x96510 (DECIMAL 615696 — the "614672" on the dispatch
// list is another decimal-rva typo; 614672 = 0x96110 is a different chunk).
// 39 B code + 9 B (8bff + 8da424) pad. C + 4-patch hybrid (probes v4..v6).
//
// Args: G_UHline(*(short*)(p+2), *(short*)(p+4), *(short*)(p+0)) — CL stages
// arg3 [p+0]->eax, arg2 [p+4]->ecx, arg1 [p+2]->edx (matching FA's movsx
// order) and interleaves add esi,6 into the push stream naturally.
//
// Root cause (why not pure C): CL's CSE caches the 0x80 mask constant in
// ebx across the two test sites (v4/v5/v6 — while form, split head/loop
// bases, and volatile loads all produced the identical prologue):
//   push ebx; mov al,[ecx+1]; push esi; mov ebx,0x80; mov esi,ecx;
//   test bl,al; jne; ... test [esi+1],bl; je; ... pop esi; pop ebx; ret
// FA keeps both tests mem-immediate with no ebx:
//   push esi; mov esi,ecx; test byte [ecx+1],0x80; jne;
//   ... test byte [esi+1],0x80; je; ... pop esi; ret
// Unsteerable (same shape from three spellings) → 4 patches below, all
// scheduler/peephole deltas, no addend semantics. The lone reloc (call
// rel32 to _G_UHline@12, content 0) auto-shifts 0x22 → 0x1a in fitobj.
//
// Patch directives (CL-obj offsets, decimal, fitobj --patch syntax):
//   patch 0:16->9:  568bf1f6410180751c
//       (drop push ebx/al-load/ebx=0x80/reg-test; restore FA head incl.
//        jne disp 1c -> 0x25 loop exit)
//   patch 31:3->4:  f6460180  (test [esi+1],bl -> test [esi+1],0x80)
//   patch 35:2->2:  74e4      (je retarget -> 0x09 loop head)
//   patch 25:3->2:  5ec3      (drop pop ebx)
// Net 46 -> 39 B. Fit: fitobj G_DrawYLR_final.obj 615696 + the 4 --patch
// strings; byte-verify passes, tail census-proven (8bff+8da42400000000).
// Maps: none (_G_UHline@12 is the identity FA anchor).
extern int __stdcall G_UHline(int a, int b, int c);

void __fastcall G_DrawYLR(int rec)
{
    char *p = (char *)rec;
    while (!(*(unsigned char *)(p + 1) & 0x80)) {
        G_UHline(*(short *)(p + 2), *(short *)(p + 4), *(short *)(p + 0));
        p += 6;
    }
}