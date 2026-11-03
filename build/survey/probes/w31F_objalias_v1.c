/* w31F / @OBJAlias@8 @ rva 587296 (0x8f620) 112 B FPO/esp fastcall @8
 * FA: mov ax,cx; push ebx; test dl,dl; je Lelse
 *   flag arm: test ax,ax; jl exit(ax=id); edx=objPtrs[(unsigned short)ax];
 *             cx=WORD[edx+0x74]; test; je exit(ax=id); mov ax,cx; exit
 *   else arm: dx=ax; test dx; jge exit(ax=id);
 *             i=1; cmp WORD[nextObjId],i; jbe exit(0);
 *             L: ecx=i&0xffff; ebx=objPtrs[i]; cx=[ebx+0x74]; test cx,cx ->
 *                wait: cmp WORD PTR [ebx+0x74],dx; je exit(ax=i);
 *                inc eax; xor ecx,ecx; mov cx,[nextObjId]; cmp ecx,eax;
 *                jg L; exit: xor ax,ax; pop ebx; ret */
extern unsigned short nextObjId;
extern unsigned long objPtrs[1];

short __fastcall OBJAlias(short id, char flag)
{
    if (flag) {
        if (id < 0)
            return id;
        {
            unsigned long *po = objPtrs + (unsigned short)id;
            short a = *(short *)((char *)*po + 0x74);
            return a ? a : id;
        }
    } else {
        if (id >= 0)
            return id;
        {
            unsigned short i = 1;
            while ((unsigned short)i < nextObjId) {
                unsigned long o = objPtrs[(unsigned short)i];
                if (*(short *)((char *)o + 0x74) == id)
                    return (short)i;
                i++;
            }
        }
        return 0;
    }
}