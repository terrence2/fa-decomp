// _atexit @ rva 0xe27c0 (19 B) — mov eax,[esp+4] / push eax / call __onexit /
//   add esp,4 / cmp eax,1 / sbb eax,eax / neg eax / ret — the boolean of
//   "the __onexit registration returned a non-null handler".
// Codegen note: FA's revision picks cmp1/sbb/neg here (like CTEval_do_nothing's
// borrow form); if our CL picks mov1/adc-[-1] instead, the entry carries the
// same-class patch.
extern int onexitFn(void (*fn)(void));

int __cdecl atexit_(void (*fn)(void))
{
    return onexitFn(fn) >= 1;
}