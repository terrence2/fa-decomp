// __callnewh @ rva 0xdf5d0 (62 B) — _callnewh(unsigned long size): the
// new-handler hook under the _LOCK_NUMBER(9) malloc lock. lock(9); if
// __pnhHeap is set, call it (fn-ptr through eax; FA loads the size arg
// after the null test: mov ecx,[esp+4]/push ecx); success first:
// _unlock(9)/return 1 inline, both failures fall to the shared tail
// _unlock(9)/xor/ret at 0x4df601. Plain C; success-first polarity.
extern void __cdecl _lock(int n);
extern void __cdecl _unlock(int n);
extern int (*_pnhHeap)(int);

int __cdecl _callnewh(unsigned long size)
{
    _lock(9);
    if (_pnhHeap != 0)
        if (_pnhHeap(size) != 0)
        {
            _unlock(9);
            return 1;
        }
    _unlock(9);
    return 0;
}