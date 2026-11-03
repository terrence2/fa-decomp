/* w31F / _OBJAliasPreferred@16 @ rva 587632 (0x8f770) 96 B FPO/esp stdcall
 * FA: push esi; esi=[esp+8](arg1); test esi,0x80000000; je skip;
 *   return esi. skip: ecx=esi&0x1fffffff; test ecx,0x10000000; je;
 *   or ecx,0xe0000000; edx=[esp+0xc](arg2); call @OBJAlias@8;
 *   and eax,0xffff; ecx=[esp+0x10](arg3); and ecx,0xffff; cmp ecx,eax;
 *   jne L; eax=[esp+0x14](arg4); and eax,0xffff;
 *   L: xor eax,esi; and eax,0x1fffffff; xor eax,esi; pop esi; ret 0x10 */
extern long __fastcall OBJAlias(long id, long flag);

unsigned long __stdcall OBJAliasPreferred(unsigned long obj, long a2,
                                          unsigned long a3,
                                          unsigned long a4)
{
    unsigned long key, r;
    if (obj & 0x80000000)
        return obj;
    key = obj & 0x1fffffff;
    if (key & 0x10000000)
        key |= 0xe0000000;
    r = (unsigned long)OBJAlias(key, a2) & 0xffff;
    if ((a3 & 0xffff) == r)
        r = a4 & 0xffff;
    return ((r ^ obj) & 0x1fffffff) ^ obj;
}