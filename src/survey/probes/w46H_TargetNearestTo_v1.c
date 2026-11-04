/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0x13e50
 * (@TargetNearestTo@12, 177 B code + 15 B census tail 8d642400 x2 +
 * 8da424..). CL output is discarded by the fitobj rebuild; husk must merely
 * keep a .text section alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: fastcall-ish (edx saved into [esp+4], plus 1 stack arg = 12
 * bytes param area, ebp, 2 locals). For i < _numVisibleTargets: id =
 * word[esi + _visibleTargetIds]; if Targetable@16(id,1,1,1): eax = |(short)
 * word[ebp] - arg1| << 8 / dword[0x5535b6] (_grMode+6) via idiv [mem];
 * ecx = eax; eax = |(short)word[ebp+2] - arg2| + ecx. If [esp+0x10] > eax
 * or edi == -1: edi = i, [esp+0x10] = eax. Return edi or word 0 (xor ax,ax
 * when edi==-1). 15 B census tail.
 */
int w46h_targetnearestto_stub(void) { return 0; }