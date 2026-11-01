// @HARDResourceName@4 @ rva 0x52e90 — name is UNINITIALIZED (no c7 init
//   store, d101 v1) passed by &name to HARDPtrs, then the result is
//   DEREFERENCED once (*name) into t52eb0 (probe d101 exact).
extern void *__fastcall t52eb0(char *name);
extern char *__stdcall HARDPtrs(int a, char **out, int f);

void *__fastcall HARDResourceName_q(int a)
{
    char *name;
    HARDPtrs(a, &name, 0);
    return t52eb0(*(char **)name);
}
