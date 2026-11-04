/* _WPObj@4 @ rva 0x97a80 (80 B) — stdcall ushort(void*):
   switch on ((char*)o)[3]: 0/1 -> 0; 2 -> *(ushort*)(o+4);
   3 -> wpSync(*(ushort*)(o+4)); default -> 0 (trailing return). */
extern unsigned short __fastcall w28a_wpSync(unsigned short w);
    /* =$FA$_t_45dc60 */

unsigned short __stdcall w28a_WPObj(void *o)
{
    switch (*(unsigned char *)((char *)o + 3)) {
    case 0:
    case 1:
        return 0;
    case 2:
        return *(unsigned short *)((char *)o + 4);
    case 3:
        return w28a_wpSync(*(unsigned short *)((char *)o + 4));
    }
    return 0;
}
