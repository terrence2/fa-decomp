// @CPRadarRange@4 @ rva 0x3d850 (48 B) — FA asm: mov eax,<ifmScale+0x3f8>
//   (a1) / add eax,ecx (fastcall param) / mov <..+0x3f8>,eax (a3 store) /
//   jns L1 / mov dword <..+0x3f8>,0 (c7 05) / ret / L1: mov
//   <..+0x3f8>,eax (a3 store AGAIN — the >=0 path re-stores) / cmp eax,5 /
//   jle ret / mov dword <..+0x3f8>,5 (c7 05) / ret.  CPBombRange (0x3e260)
//   is the _bombRange twin.  Volatile-typed accesses keep CL's CSE from
//   dropping the second a3 store (v1 plain C lost it; v3 naked asm gave the
//   same bytes — volatile wins, probe b18_CPRadarRange_v2.obj).
extern char ifmScale[];

void __fastcall CPRadarRange(int add)
{
    volatile long *g = (volatile long *)(ifmScale + 0x3f8);
    long v;
    v = *g + add;
    *g = v;
    if (v < 0) {
        *g = 0;
        return;
    }
    *g = v;
    if (v > 5)
        *g = 5;
}