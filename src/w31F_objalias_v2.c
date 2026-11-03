/* w31F / @OBJAlias@8 @ rva 587296 (0x8f620) 112 B FPO/esp fastcall @8
 * v2: else-arm counter spelled int (FA: b8/mov eax,1, inc eax, jg latch);
 * flag-arm as if(a) return a; return id; */
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
        if (id >= 0)
            return id;
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