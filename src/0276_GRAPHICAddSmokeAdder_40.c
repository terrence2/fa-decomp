/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0x435b0
 * (_GRAPHICAddSmokeAdder@40, 135 B code + 9 B census tail 8bff + 8da424..).
 * CL output is discarded by the fitobj rebuild; husk must merely keep a
 * .text section alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: ebx = GRAPHICAddInvisible(9 stack args, 1); GRAPHICMakeAdder(6
 * args) over the dup'd arg dwords; if ebx, set byte[ebx+0x65] = low arg byte;
 * if that byte == _thisComputer, MPGraphicAddSmokeAdder(10 args) with the
 * same dup'd push pattern (eax/ecx/edx triples). Returns ebx.
 */
int w46h_graphicaddsmokeadder_stub(void) { return 0; }