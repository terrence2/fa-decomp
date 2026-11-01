// _abort @ rva 0xe2820 (31 B) — push 0xa (RT_ABORT) / call __NMSG_WRITE /
//   add esp,4 / push 0x16 (SIGABRT) / call _raise / add esp,4 / push 3 /
//   call __exit / add esp,4 / ret.
extern void __cdecl _NMSG_WRITE(int msg);
extern int __cdecl _raise(int sig);
extern void __cdecl _exit(int c);

void __cdecl abort_(void)
{
    _NMSG_WRITE(10);
    _raise(22);
    _exit(3);
}