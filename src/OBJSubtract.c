// _OBJSubtract@0 @ rva 0x8f5f0 (48 B) — FA asm: 66 a1 [nextObjId] / 33 c9 /
// 66 48 dec ax / 66 a3 store-back / 25 ffff 0000 / 8b 14 45 .. (eax*2 sib into
// the comment-type table at ?COMMENT_TYPE@@3W4__unnamed@@A+0x150) / 66 3b (movsx)
// / sub [?COMMENT_TYPE@@3W4__unnamed@@A+0x858], eax. Plain C --nextObjId +
// table-indexed subtract matched (probe b17c_objsubtract_v1 byte-exact, incl.
// the and 0xffff zero-extend and (long)(ushort) conversion). Double-addend
// rule: the C refs are the bare aliases (baked disp 0) — addends +0x150 /
// +0x858 live ONLY in the maps.
extern unsigned short nextObjId;
extern unsigned short ctTbl[];   /* _ctTbl = ?COMMENT_TYPE@@3W4__unnamed@@A+0x150 */
extern long ct858;               /* _ct858 = ?COMMENT_TYPE@@3W4__unnamed@@A+0x858 */

void OBJSubtract(void)
{
    long i = (long)(--nextObjId);
    ct858 -= ctTbl[i];
}