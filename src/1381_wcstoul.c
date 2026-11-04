// _wcstoul @ rva 0xe2560 (26 B) — same forward as _wcstol with flag 1.
//   map: _stolQ=$FA$_t_4e2350 (unnamed chunk anchor).
extern long __cdecl _stolQ(const unsigned short *s, unsigned short **e, int base, int neg);

long __cdecl wcstoul(const unsigned short *s, unsigned short **e, int base)
{
    return _stolQ(s, e, base, 1);
}