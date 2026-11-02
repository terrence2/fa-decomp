// ?CN_GetBigString@@YAJPADPAE@Z @ rva 0x7e4b0 (32 B) — thunk into
// ?_GetString@@YAJPAD00JJJ@Z with the .rdata format string pushed as an
// imm32 (68 58 43 4f 00, DIR32 to _fmtReduceButtonH+0x1a4) and the two
// params re-fetched into eax/ecx after the first push (6a 4e / 8b 44 24 08).
// .cpp (the call target carries C++ mangling); data extern is "C" so it
// stays _fmtReduceButtonH — identity map, no C++-mangle LNK2001 here.
extern "C" char fmtReduceButtonH[];

long _GetString(char* a, char* b, char* c, long d, long e, long f);

int CN_GetBigString_q(char* p1, unsigned char* p2)
{
    return (int)_GetString(p1, (char*)p2, fmtReduceButtonH + 0x1a4, 0x28, 0x19, 0x4e);
}