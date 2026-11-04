// ?fnc_toCallDuringAnswer@@YAHH@Z @ rva 0x98710 (32 B) — FA asm: push 0 /
//   push 0x64 / ff 15 <appIO> (call dword ptr [appIO] — appIO is the net
//   layer's fn-pointer extern) / add esp,8 / 83 f8 01 / 1b c0 / 40 / ret —
//   appIO(100, NULL) (cdecl, right-to-left: 0 = char* first) and return the
//   bool of the answer callback firing, i.e. whether appIO returned >= 1.
//   The cmp1/sbb/inc tail is the unsigned-short r>=1 borrow form (w2_cont
//   precedent); on the 32-bit return CL picks it from `unsigned long r`.
// Plain C exact (probe b19c_fnc; tail = census 050 + leal).
extern long (__cdecl *appIO)(long tag, char *text);

int __cdecl fnc_toCallDuringAnswer(int mode)
{
    unsigned long r = appIO(100, 0);
    return r >= 1;
}