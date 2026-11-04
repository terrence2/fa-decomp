// ?MPShellInitMessages@@YGXXZ @ rva 0x72510 (16 B) — dword zero store into
//   ?buffRemapTbl@@3PAEA+0x80 (c7 05) and ret; the tail pad is FA's own
//   05 00 00 00 00 census filler.
extern long buffRemapTbl80[];
void __stdcall MPShellInitMessages_q(void)
{
    buffRemapTbl80[0] = 0;
}