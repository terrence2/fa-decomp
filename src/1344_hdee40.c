/* wave 32 batch B: 0x4dee40 (unnamed, dead CRT _open wrapper -> _sopen w/ _SH_DENYNO 0x40) */
extern int _sopen(const char *path, int oflag, int shflag, int pmode);

/* FA bytes 0x4dee40 (26 B):
   8b 44 24 0c        mov  eax,[esp+0xc]
   8b 4c 24 08        mov  ecx,[esp+0x8]
   8b 54 24 04        mov  edx,[esp+0x4]
   50 6a 40 51 52     push eax / push 0x40 / push ecx / push edx
   e8 (rel)           call _sopen
   83 c4 10 c3        add esp,0x10 / ret
   = int f(path, oflag, pmode) { return _sopen(path, oflag, 0x40, pmode); }
   push order RTL: pmode, 0x40, oflag, path.
   reg plan: edx=a1, ecx=a2, eax=a3 (loads in reverse order a3,a2,a1) */
int w32b_sopenw(const char *path, int oflag, int pmode)
{
    return _sopen(path, oflag, 0x40, pmode);
}