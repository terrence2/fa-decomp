/* w31F / _T_ObjList@8 @ rva 674928 (0xa4c70) 96 B FPO/ebp stdcall @8
 * v2: InBounds args swapped (FA arg1 = o+0x11 record, arg2 = a1 point);
 * char returns for both InBounds and cb (FA tests al,al);
 * explicit mask local to get FA's mask-reg/idx-reg split. */
extern unsigned short nextObjId;
extern unsigned long objPtrs[1];
extern char __stdcall InBounds(long a, char *b);

void __stdcall T_ObjList(long a1, char (__cdecl *cb)(long))
{
    unsigned long o, mask;
    unsigned short i = 1;
    while (i < nextObjId) {
        o = objPtrs[(unsigned short)i];
        mask = i;
        if (*(unsigned long *)(((char *)o) + 1) & mask) {
            if (InBounds((long)(((char *)o) + 0x11), (char *)a1)) {
                if (!cb(i))
                    break;
            }
        }
        i++;
    }
}