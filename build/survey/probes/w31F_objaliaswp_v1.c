/* w31F / _OBJAliasWaypoint@16 @ rva 587904 (0x8f880) 96 B FPO/esp stdcall
 * FA: push ebx; push esi; esi=[esp+0xc](arg1); al=[esi+3]; cmp al,2;
 *   jne L2; cx=[esi+4](word); bl=[esp+0x10](arg2 lo byte); edx=ebx;
 *   call @OBJAlias@8; cx=[esp+0x18](arg4 word); WORD[esi+4]=ax;
 *   ax=[esp+0x14](arg3 word); cmp WORD[esi+4],ax; jne L3; WORD[esi+4]=cx;
 *   jmp L3; L2: ax=[esp+0x14]; bl=[esp+0x10]; cx=[esp+0x18];
 *   L3: edx=[esi+0x21]; test edx; je L4; push ecx; push eax; push ebx;
 *   push edx; call _OBJAliasPreferred@16; [esi+0x21]=eax;
 *   L4: pop esi; pop ebx; ret 0x10 */
extern long __fastcall OBJAlias(long id, long flag);
extern long __stdcall OBJAliasPreferred(unsigned long a, char b,
                                        unsigned short c, unsigned short d);

void __stdcall OBJAliasWaypoint(char *p, char c1, unsigned short w1,
                                unsigned short w2)
{
    unsigned short r;
    if (*(unsigned char *)(p + 3) == 2) {
        r = OBJAlias(*(unsigned short *)(p + 4), c1) & 0xffff;
        *(unsigned short *)(p + 4) = r;
        if (*(unsigned short *)(p + 4) == w1)
            *(unsigned short *)(p + 4) = w2;
    }
    if (*(unsigned long *)(((char *)p) + 0x21))
        *(unsigned long *)(((char *)p) + 0x21) = OBJAliasPreferred(
            *(unsigned long *)(((char *)p) + 0x21), c1, w1, w2);
}