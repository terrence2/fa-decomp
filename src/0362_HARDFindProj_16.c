/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0x52610
 * (_HARDFindProj@16, 166 B code + 10 B census tail 8d4900 + 8da424..). CL
 * output is discarded by the fitobj rebuild; husk must merely keep a .text
 * section alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: return -1 if !byte[_curThingType+0xb5] (test + 90 nop pad).
 * ebx = arg1 + arg2 (signed-add clamp loop: jns skip / xor ebx,ebx ->
 * byte[_curThingType+0xb5]-1), bounded by the type-count byte. Loop:
 * HARDPtrs@12(ebx, &local, 0); if p && p[0]==7 && (dword[p+0xa6]&0x80):
 * arg3 nonzero -> found, else arg4 nonzero -> found (jmp 0x4526aa); i++
 * while count > i.
 */
int w46h_hardfindproj_stub(void) { return 0; }