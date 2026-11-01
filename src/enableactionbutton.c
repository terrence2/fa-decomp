// @EnableActionButton@4 @ rva 0x8b240 (16 B) — and WORD PTR [eax],0x7fff
extern void *__fastcall DialogGetPtr(int);

void __fastcall EnableActionButton(int a)
{
    *(volatile unsigned short *)DialogGetPtr(a) &= 0x7fff;
}
