/* rva 0xbf250 (782928), 112 B - _PROJRadarIsOn@8: goto-tail return-1 so
   CL keeps the ja/jle jumps to the shared mov al,1. */
extern unsigned short w34g_ct;    /* -> _currentT */

char __stdcall PROJRadarIsOn2(void *s, short dt)
{
    if (*(unsigned char *)((char *)s + 0x10) & 0x80)
    {
        if (*(unsigned short *)((char *)s + 0x11a) > w34g_ct)
            goto ret1;
        return 0;
    }
    if (!(*(unsigned *)((char *)s + 0xde) & 0x400))
        return 0;
    if ((short)dt + (unsigned short)w34g_ct >
        (unsigned short)*(unsigned short *)((char *)s + 0x11a))
    {
        *(unsigned short *)((char *)s + 0x11a) =
            (unsigned short)(w34g_ct + (unsigned short)dt);
    }
ret1:
    return 1;
}