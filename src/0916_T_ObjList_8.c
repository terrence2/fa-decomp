/* w31F / _T_ObjList@8 v3: mask staged BEFORE the index (FA: mov ebp,ebx then
 * mov eax,ebx / and eax,0xffff / objPtrs[eax]); counter 32-bit homed (FA bb).
 * index spelled i & 0xffff to keep it off the mask's SSA value. */
extern unsigned short nextObjId;
extern unsigned long objPtrs[1];
extern char __stdcall InBounds(long a, char *b);

void __stdcall T_ObjList(long a1, char (__cdecl *cb)(long))
{
    unsigned int i = 1;
    unsigned long o, mask;
    while (i < nextObjId) {
        mask = (unsigned long)i;
        o = objPtrs[(unsigned short)(i & 0xffff)];
        if (*(unsigned long *)(((char *)o) + 1) & mask) {
            if (InBounds((long)(((char *)o) + 0x11), (char *)a1)) {
                if (!cb((long)i))
                    break;
            }
        }
        i++;
    }
}