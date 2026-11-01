// __errno @ rva 0xd99b0 (9 B, FPO cbProlog=0)
// FA asm: call __getptd / add eax,8 / ret
//   -> returns char* 8 past the per-thread data block.
extern char *__cdecl _getptd(void);

char *__cdecl _errno(void)
{
    return _getptd() + 8;
}