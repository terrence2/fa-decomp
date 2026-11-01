// ?MyFilterProc@@YADPAGPAJPAD@Z @ rva 0x7f080 (16 B) — char __cdecl filter
//   proc for the brief/map screen window class (unsigned short*, long*,
//   char* params, all unused at stub level): FA asm is just 32 c0 c3
//   (xor al,al — the char-0 return idiom, wave-5 d62 family) + census lea
//   pads. Plain C exact (probe b19c_mfp).
char __cdecl MyFilterProc(void *a, long *b, char *c)
{
    return 0;
}