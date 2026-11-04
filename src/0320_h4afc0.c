/* gap chunk rva 0x4afc0 (16 B): cdecl void(void*): o=*(arg); flag=*(o+0x196);
   *(uchar*)(flag+0x1c) = 1. Reads [esp+4] -> stack arg, ret = cdecl. */
void __cdecl w28a_ROSetFlag(void *o)
{
    *(unsigned char *)(*(unsigned long *)((char *)o + 0x196) + 0x1c) = 1;
}
