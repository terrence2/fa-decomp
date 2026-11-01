// __tzset @ rva 0xe3d40 (26 B) — push 0xb / call __lock / add esp,4 /
//   call $FA$t_4e3d60 (helper, cdecl 0 args) / push 0xb / call __unlock /
//   add esp,4 / ret — read the TZ variable under the 0xb (=11, _TZ_LOCK)
//   lock.
extern void __cdecl _lock(int n);
extern void __cdecl _unlock(int n);
extern void tzsetHelper(void);

void __cdecl _tzset(void)
{
    _lock(11);
    tzsetHelper();
    _unlock(11);
}