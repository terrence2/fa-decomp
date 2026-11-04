// @CPToggleHistory@0 @ rva 252032 (0x3d880, 16 B) — patch-hybrid.  The
//   plain-C body `windowTypes[0x3f0] = windowTypes[0x3f0] == 0;` (w6_t7
//   recipe: value kept in AL end-to-end so the store emits a2) reproduces
//   7/16 bytes; CL still emits `80 3d <imm> 00 | 0f 94 c1 | 88 0d <imm> | c3`
//   (setne into CL then store via 88 0d) where FA has the store folded into
//   the setcc: `0f 94 c0 | a2 <imm> | c3` (setne al + a2 moffs store) —
//   CL 4.2 will not emit setcc-AL directly followed by an a2 moffs store.
//   The 10-B span 0f94c1..c3 at offset 7 is replaced with FA's
//   0f94c0+imm+c3, the windowTypes+0x3f0 address site retargeted onto the
//   fresh winT3f0 symbol.
//   Probe build/survey/probes/p_w23_CPToggleHistory_patch2.obj EXACT
//   (w23_r4.json; ladder w23_CPToggleHistory_v1/patch w/ wrong span/offset
//   rounds — the setcc span starts at offset 7, not 6).
//   Maps (swap.json verbatim + patch site): winT3f0=_windowTypes+0x3f0.
//   Patch: "7,10,0f94c0a200000000c3,4:6:winT3f0".
extern unsigned char windowTypes[];

void CPToggleHistory(void)
{
    windowTypes[0x3f0] = windowTypes[0x3f0] == 0;
}