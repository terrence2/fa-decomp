// @GetExecutablePath@8 @ rva 0xaa260 — GetModuleFileNameA(0, buf, size&0xffff)
//   boolean: FA masks the SECOND (fastcall edx=size) param with 81 e2 and
//   pushes edx first — C arg order (masked, other) is wrong; the masked value
//   is the size (probe d83 exact).
__declspec(dllimport) int __stdcall GetModuleFileNameA(int h, char *b, int n);

char __fastcall GetExecutablePath_q(char *b, int n)
{
    return (char)(GetModuleFileNameA(0, b, n & 0xffff) != 0);
}
