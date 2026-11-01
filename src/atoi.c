// _atoi @ rva 0xd3a90 (12 B) — mov eax,[esp+4] / push eax / call _atol /
//   add esp,4 / ret — atoi delegates to atol.
extern long __cdecl atol_p(const char *s);

int __cdecl atoi_(const char *s)
{
    return (int)atol_p(s);
}