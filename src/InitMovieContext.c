// ?InitMovieContext@@YAXPAUMovieContext@@JJ@Z @ rva 0x41980 (16 B) — FA
//   asm: mov eax,[esp+4] / c7 40 14 00 00 00 00 (mc->field@0x14 = 0) / ret;
//   the two long params are accepted but unused. Plain C exact (probe
//   b19c_imc; tail = census 8d 64 24 00).
void __cdecl InitMovieContext(void *mc, long a, long b)
{
    *(long *)((char *)mc + 0x14) = 0;
}