/* w31F / @OBJAlias@8 v3: else-arm stages a distinct id local first (FA's
 * mov dx,ax before test dx,dx), int counter (FA: mov eax,1 / inc eax / jg). */
extern unsigned short nextObjId;
extern unsigned long objPtrs[1];

short __fastcall OBJAlias(short id, char flag)
{
    if (flag) {
        if (id < 0)
            return id;
        {
            short a = *(short *)((char *)objPtrs[(unsigned short)id] + 0x74);
            if (a)
                return a;
        }
        return id;
    } else {
        {
            short idv = id;
            if (idv >= 0)
                return idv;
        }
        {
            long i = 1;
            while (i < nextObjId) {
                unsigned long o = objPtrs[(unsigned short)i];
                if (*(short *)((char *)o + 0x74) == id)
                    return (short)i;
                i++;
            }
        }
        return 0;
    }
}