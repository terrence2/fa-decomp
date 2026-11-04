// 0xd4980 gap chunk (16 B) — v1
extern void * __cdecl w28c_nhMalloc(unsigned long size, long mode);

void * __cdecl w28c_t4d4980(unsigned long size)
{
    return w28c_nhMalloc(size, 1);
}
