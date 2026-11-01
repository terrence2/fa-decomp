// @DialogItemIsEnabled@4 @ rva 0x8b2a0 (16 B)
// FA: call DialogGetPtr / test BYTE PTR [eax+1],0x80 / sete cl / mov al,cl / ret
extern void *__fastcall DialogGetPtr(int);

char __fastcall DialogItemIsEnabled(int a)
{
    const unsigned char *p = (const unsigned char *)DialogGetPtr(a);
    return !(p[1] & 0x80);
}
