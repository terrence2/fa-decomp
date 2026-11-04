/* v3: fn-ptr member returns int (FA's 83 f8 ff 3-byte cmp eax,-1),
 * outer function still returns char (32 c0 / b0 01). */
#pragma pack(push, 1)
struct W36G_WSFN { unsigned char pad36[0x36];
                   int (__stdcall *ws_ioctl)(unsigned long, long,
                                             unsigned long *); };
#pragma pack(pop)
extern struct W36G_WSFN w36g_ws;    /* ?ws@@3U_winsock_funcs@@A */
extern char *winsock_handle_error(char *, int, char *, int);
extern char *w36g_wstr2[];          /* ?wsa_string2@@3PAPADA (array of char*) */

char winsock_set_non_blocking(unsigned long s, int m)
{
    unsigned long flag = 1;
    if (w36g_ws.ws_ioctl(s, 0x8004667e, &flag) == -1) {
        winsock_handle_error((char *)&w36g_wstr2[0x81], 1,
                             (char *)&w36g_wstr2[0x83], 700);
        return 0;
    }
    return 1;
}