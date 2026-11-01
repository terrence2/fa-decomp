// _is_wctype @ rva 0xe4600 — loads BOTH params into regs then pushes
//   arg2-first: identity forward iswctype(a, b) (d89/d106 exact; the
//   swapped-arg form loaded [esp+4] first, d89 v1).
extern int iswctype(int a, int b);

int _is_wctype_q(int a, int b)
{
    return iswctype(a, b);
}
