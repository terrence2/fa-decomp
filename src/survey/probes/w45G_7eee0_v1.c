/* w45G wave-45 batch G: whole-body transplant husk for FA rva 0x7eee0.
 * CL output is discarded by the fitobj rebuild (symbol table replaced
 * by FA's own via the maps/newsite patch band); husk must merely keep
 * a .text section alive (non-static, else /O2 drops the TU body).
 */
int w45g_7eee0_stub(void) { return 0; }
