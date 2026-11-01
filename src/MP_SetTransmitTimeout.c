// ?MP_SetTransmitTimeout@@YAXJ@Z @ rva 0x92e90 (10 B code + 6 B 8d9b pad) —
// mov eax,[esp+4] / a3 moffs dword store / ret.  mpInfoArr + 0x150 baked in
// the C expression (map TO is the bare ?mpInfo@@3UMP_INFO@@C anchor;
// double-addend rule).  Plain C, probe w16c_2 exact.
extern char mpInfoArr[];

void MP_SetTransmitTimeout(long t)
{
    *(long *)(mpInfoArr + 0x150) = t;
}