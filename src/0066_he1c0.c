/* gap chunk rva 0xe1c0 (32 B): fastcall void — MMFreePtr(*(t+0x60)); t+60/54/58/5c = 0.
   FA: push esi / mov esi,ecx / mov ecx,[ecx+0x60] / call @MMFreePtr@4 /
   xor eax,eax / 4x mov [esi+off],eax (60,54,58,5c) / pop esi / ret. */
extern void __fastcall MMFreePtr(void *p);

void __fastcall w30b_fq(void *t)
{
    MMFreePtr(*(void **)((char *)t + 0x60));
    *(void **)((char *)t + 0x60) = 0;
    *(void **)((char *)t + 0x54) = 0;
    *(void **)((char *)t + 0x58) = 0;
    *(void **)((char *)t + 0x5c) = 0;
}