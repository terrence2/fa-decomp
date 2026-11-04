// _wcstol @ rva 0xe2330 (26 B) — wide strtol: 4-arg forward to the core chunk
//   at 0x4e2350 with the negative-flag constant 0.  Right-to-left emission with
//   the next-to-push stack param fetched first (FA CRT pattern, cf __atoldbl).
//   map: _stolQ=$FA$_t_4e2350 (unnamed chunk anchor).
extern long __cdecl _stolQ(const unsigned short *s, unsigned short **e, int base, int neg);

long __cdecl wcstol(const unsigned short *s, unsigned short **e, int base)
{
    return _stolQ(s, e, base, 0);
}