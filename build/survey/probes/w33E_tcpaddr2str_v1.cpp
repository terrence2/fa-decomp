/* FA chunk ?tcpaddr2str@@YADPAUNET_ADDRESS@@PAD@Z rva 0xa8e50 (80 B) —
   wave 33 batch E probe v1. Tests family==1 then Sprintf's the four
   address bytes decimal-dot-separated. The format literal lives inside
   FA's ?videoInitialized@@3DA data chunk at +0x414 = 0x4e7cfc. */
struct _NET_ADDRESS { short family; unsigned long addr; };
extern char tcpaddr2strFmt[];   /* = ?videoInitialized@@3DA+0x414 */
extern "C" void __cdecl Sprintf(char *dst, char *fmt, ...);

char tcpaddr2str(_NET_ADDRESS *a, char *buf)
{
    if (a->family != 1)
        return 0;
    Sprintf(buf, tcpaddr2strFmt, a->addr >> 24, (a->addr >> 16) & 0xff,
            (a->addr >> 8) & 0xff, a->addr & 0xff);
    return 1;
}