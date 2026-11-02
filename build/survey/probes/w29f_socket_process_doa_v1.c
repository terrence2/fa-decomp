// 0xa3650 ?socket_process_doa@@YAXXZ — v1
extern unsigned long w29fSLCount;   /* -> ?socket_list@@3USOCKET_STATE_LIST@@A+0x314 */
extern unsigned long w29fSLArr[];   /* -> ?socket_list@@3USOCKET_STATE_LIST@@A+0x318 */
extern void __cdecl w29fSockCloseX(unsigned long h);

void __cdecl socket_process_doaX(void)
{
    unsigned long *p = w29fSLArr;
    unsigned long i = 0;
    for (i = 0; i < w29fSLCount; i++) {
        w29fSockCloseX(*p);
        p++;
    }
    w29fSLCount = 0;
}