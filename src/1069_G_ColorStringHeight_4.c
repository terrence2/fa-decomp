// @G_ColorStringHeight@4 @ rva 0xb49c0 (16 B)
//   call @MMAccessR@4 (fastcall, reads ecx) / mov eax,[eax+0x2a] /
//   movsx eax,word [eax+0xc4] / ret
extern int __fastcall MMAccessR(int);

int __fastcall G_ColorStringHeight(int h)
{
    int o = *(int *)((char *)MMAccessR(h) + 0x2a);
    return *(short *)((char *)o + 0xc4);
}
