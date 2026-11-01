// _DistToObj@8 @ rva 0x11d50 (33 B code + 15 B 8d64/8d64/8da4 pad) —
//   mov eax,[esp+8] / mov ecx,[esp+4] / and eax,0xffff /
//   mov eax,[eax*4+_objPtrs] / add eax,0x11 / push eax / push ecx /
//   call _Dist@8 / ret 8.
// Plain C emits the whole plan exactly (probe w16c_5): right-to-left eval
// keeps p1 in ecx from the entry load, the sib load is the plain C array
// index form.  objPtrs/_Dist@8 are FA.SMS identities, no maps.
extern long objPtrs[];
extern long __stdcall Dist(int a, int b);

long __stdcall DistToObj(int a, int b)
{
    return Dist(a, objPtrs[b & 0xffff] + 0x11);
}