/* rva 670128 (0xa39b0) 32 B FPO/esp gap chunk
 * fastcall (ecx=struct ptr, edx=val): if ((p)[0xe] & 2)
 * return _MMAccessE@12(*(long *)(p + 0xf), 0, v); else *(long *)(p + 0xf) */
extern long __stdcall MMAccessE(long a1, long a2, long a3);

long __fastcall w30h_mmAccessVal(void *p, long v)
{
    if (((unsigned char *)p)[0xe] & 2)
        return MMAccessE(*(long *)((char *)p + 0xf), 0, v);
    return *(long *)((char *)p + 0xf);
}