// _CTEval_do_evade @ rva 0x64000 (16 B) — xor eax,eax / cmp word[+50],1 /
//   sete al / ret  (C: tick == 1)
extern unsigned short serviceTicks[];

long __cdecl CTEval_do_evade(void)
{
    return *(unsigned short *)(serviceTicks + 0x28) == 1;
}
