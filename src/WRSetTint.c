// @WRSetTint@4 @ rva 0xaf510 (32 B) — fastcall tint index t in ecx: load
// hdr[t] via the [ecx*4 + _hdr] sib, tint = t (89 0d), currentTintTable =
// tbl (a3 moffs eax store). All three externs are FA.SMS identity symbols
// (_hdr / _tint / _currentTintTable); probe w11a_04_wst1, byte-exact —
// CL emitted the a3 store in plain C here (naked asm w11a_05 identical).
extern int hdr[];
extern int tint;
extern int currentTintTable;

void __fastcall WRSetTint_q(int t)
{
    int tbl = hdr[t];
    tint = t;
    currentTintTable = tbl;
}