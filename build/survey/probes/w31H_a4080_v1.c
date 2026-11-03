/* w31H_a4080 v1: FA bytes (rva 0xa4080, 28 B code + 4 B pad): push esi;
   mov esi,[esp+8]; mov eax,[esi]; test eax,eax; je L; push 0x8000; push eax;
   call _RMAccess@8 (FA public, stub t00093); mov [esi],eax; L: pop esi;
   ret 4. stdcall 1 param; right-to-left args: (value, 0x8000). */
long __stdcall RMAccess(long val, long flg);
void __stdcall w31h_a4080(void **pp)
{
    if (*pp) *pp = (void *)RMAccess((long)*pp, 0x8000);
}