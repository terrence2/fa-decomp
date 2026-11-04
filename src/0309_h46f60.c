// w41C candidate 0x46f60 (rva 290656, 41 B code + 7 B census pad) —
// unreferenced gap chunk (no rel32 callers, no data refs): cdecl, 4 stack
// params, calls [ [p1+0x17a] + 4 ] with (p1,0,0,0,p2,p3,p4).
//   8b 44 24 10 (mov eax,[esp+0x10] = p4) / 53 / 8b 4c 24 10 (=p3) /
//   50 / 8b 54 24 10 (=p2) / 51 / 8b 44 24 10 (=p1) / 52 / 6a 00 x3 /
//   8b 98 7a 01 00 00 (mov ebx,[eax+0x17a]) / 50 / ff 53 04
//   (call dword ptr [ebx+4]) / 83 c4 1c / 5b / c3.
void w41C_46f60(int p1, int p2, int p3, int p4)
{
    void (__cdecl **vt)(int, int, int, int, int, int, int);

    vt = (void (__cdecl **)(int, int, int, int, int, int, int))
        *(long **)((char *)p1 + 0x17a);
    vt[1](p1, 0, 0, 0, p2, p3, p4);
}