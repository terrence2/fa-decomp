// ?ShowDDError@CDirDraw@@SAXJ@Z @ rva 0x1dfa0 (16 B) — body is a bare c3.
// The mangling says __stdcall member but FA's retail body has no ret 4;
// reproduce with a cdecl empty body (probe w13a_showdd exact; tail =
// census lea-pad run).
void ShowDDError(long err)
{
}