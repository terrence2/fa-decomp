// @Rename@8 @ rva 0xaa110 — MoveFileA wrapper recording the 0/-1 result in
//   _dosError; probe d155 ternary (r == 1 ? 0 : -1) is FA's exact borrow form,
//   the -((unsigned)(r-1) >= 1) shape emits sbb/neg instead (d154)
__declspec(dllimport) int __stdcall MoveFileX(char *a, char *b);
extern short dosError;
int __fastcall Rename_q(char *a, char *b)
{
    int r = MoveFileX(a, b);
    return dosError = (r == 1 ? 0 : -1);
}
