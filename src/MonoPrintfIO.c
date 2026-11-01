// ?monoPrintfIO@@YAJJPAD@Z @ rva 0x5340 (16 B) — the mono printf IO
// backend, stubbed to return 0 in retail (no debug console). Body is
// plain `return 0` (xor eax,eax / ret); FPO records 2 dword params. FA.SMS
// chunk name is the mangled C++ name; no e8/abs references anywhere in
// FA (grep: 0 callers), so the C symbol _monoPrintfIO is safe. Tail pad =
// 8d9b00000000 + 8da42400000000 (padcensus VOCAB), probe w16b_5 exact.
long monoPrintfIO(long a, char *b)
{
    return 0;
}