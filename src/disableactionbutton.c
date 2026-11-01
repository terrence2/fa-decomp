// @DisableActionButton@4 @ rva 0x8b230 (16 B)
// FA: call @DialogGetPtr@4 / or WORD PTR [eax],0x8000 / ret
// volatile keeps CL's word->byte narrowing peephole out of the or
extern void *__fastcall DialogGetPtr(int);

void __fastcall DisableActionButton(int a)
{
    *(volatile unsigned short *)DialogGetPtr(a) |= 0x8000;
}
