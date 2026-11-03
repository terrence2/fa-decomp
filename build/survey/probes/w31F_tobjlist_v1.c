/* w31F / _T_ObjList@8 @ rva 674928 (0xa4c70) 96 B FPO/ebp stdcall @8
 * FA: push ebx; push esi; push edi; mov ebx,0x1; cmp WORD[nextObjId],bx;
 * jbe exit; push ebp; L-loop: esi=[esp+0x14](arg1); edi=[esp+0x18](arg2);
 * ebp=ebx; eax=ebx; and eax,0xffff; eax=objPtrs[eax];
 * test DWORD PTR [eax+0x1],ebp; je latch; push esi; add eax,0x11;
 * push eax; call _InBounds@8; test al,al; je latch; push ebx; call edi;
 * add esp,0x4; test al,al; je exit; latch: inc bx;
 * cmp WORD[nextObjId],bx; ja L-loop; exit: pop ebp; pop edi; pop esi;
 * pop ebx; ret 0x8 */
extern unsigned short nextObjId;
extern unsigned long objPtrs[1];
extern long __stdcall InBounds(long a, char *b);

void __stdcall T_ObjList(long a1, int (__cdecl *cb)(long))
{
    unsigned short i = 1;
    while (i < nextObjId) {
        unsigned long o = objPtrs[(unsigned short)i];
        if (*(unsigned long *)(((char *)o) + 1) & i) {
            if (!InBounds(a1, ((char *)o) + 0x11))
                { i++; continue; }
            if (!cb(i))
                break;
        }
        i++;
    }
    return;
}