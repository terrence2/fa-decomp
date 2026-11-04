/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0xd9e40
 * (__filbuf CRT, 245 B chunk, NO census tail: code fills chunk). CL output
 * is discarded by the fitobj rebuild; husk must merely keep a .text section
 * alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: VC4.2 _filbuf: esi=str; al=[str+0xc]; al&0x83==0 ->
 * EOF-path 0x4d9f2e; al&0x40 -> same; al&0x2 -> set 0x20 + ret -1; else
 * [str+0xc]|=1... if test eax,0x10c == 0: flush via $FA$_t_4dc580 stub;
 * else [str] = [str+8]. __read(fd=str+8val? args (edx,[str+0x18],[str+8]...)
 * fill loop at 0x4d9e86: push [str+0x18],[str+8],[str+0x10] -> __read; store
 * result [str+4]; ret on 0/-1. Tail: handle-table probe mov eax,0x51abf0
 * (__XcptActTabCount+0xc) vs [eax+0x588c70] (__crtheap+4) indexed fd lookup
 * (fd&0x1f shl 2 / fd>>& 0xffffffe7 sar 3), al&0x82 test, edx|=0x2000.
 */
int w46h_filbuf_stub(void) { return 0; }