// _setdefaultprecision (FA sym __setdefaultprecision) @ rva 0xd9360 (19 B)
//   CRT FPU setup: controlfp(PC_53, MCW_PC). Values written literally so
//   float.h's macro redefinition can't interfere.
extern unsigned int __cdecl _controlfp(unsigned int newval, unsigned int mask);

void _setdefaultprecision(void)
{
    _controlfp(0x10000, 0x30000);
}
