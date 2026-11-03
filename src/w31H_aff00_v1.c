/* w31H_aff00 v1: FA bytes (rva 0xaff00, 21 B code + 11 B pad): push esi;
   mov esi,[ecx]; sub edx,esi; imul edx,[esp+8]; sar edx,8; add edx,esi;
   pop esi; mov [ecx],edx; ret 4. __fastcall 3 args (ecx,edx,stack):
   *p = t + ((x - t) * y) >> 8. */
void __fastcall w31h_4aff00(long *p, long x, long y)
{
    long t = *p;
    *(long *)p = t + (((x - t) * y) >> 8);
}