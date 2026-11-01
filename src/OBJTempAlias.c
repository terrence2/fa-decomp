// _OBJTempAlias@0 @ rva 0x8f950 (32 B) — nextObjId+4 advance: pick
//   ?COMMENT_TYPE@@3W4__unnamed@@A+0x85c when COMMENT_TYPE+0x860 is below the
//   old value, else keep it; store selected+1 through the 89 0d store-from-ecx
//   form and return the OLD value (8b c1 copy first).  CL C forms reorder the
//   loads (nextObjId first), fold the +1 into lea ecx,[eax+1] and use a3
//   stores (w12b_OBJTempAlias2/3/5/7; the dead-increment 8b c1/41 dance is
//   asm-only) — naked asm (w12b_OBJTempAlias8 byte-exact).
extern char ctNext860[];
extern char ctBase85c[];
extern char nextObjId[];
__declspec(naked) long OBJTempAlias_q(void)
{
    __asm {
        mov eax, dword ptr [ctNext860]
        mov ecx, dword ptr [nextObjId + 4]
        cmp eax, ecx
        jge L1
        mov ecx, dword ptr [ctBase85c]
    L1:
        mov eax, ecx
        inc ecx
        mov dword ptr [nextObjId + 4], ecx
        ret
    }
}