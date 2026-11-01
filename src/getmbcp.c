// __getmbcp @ rva 0xd9e20 (6 B, FPO cbProlog=0)
// FA asm: a1 ac a7 51 00  mov eax,ds:0x51a7ac (= __mbctype+0x104)
//         c3
//   -> moffs encoding: needs CL to emit `a1 [sym]` with content 0 and the
//      +0x104 living ONLY in the link-time value; extern-array dereference
//      bakes the disp into a reloc'd moffs (content dword = 0x104).
extern unsigned char _mbctype[];

int __cdecl _getmbcp(void)
{
    return *(const int *)(_mbctype + 0x104);
}