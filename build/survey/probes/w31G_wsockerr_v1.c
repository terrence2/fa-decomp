/* chunk ?winsock_handle_error@@YAPADPADW4ERROR_SEVERITY@@0H@Z
 * @ rva 0xa2b80 (dec 666496, 48 B) — char *__cdecl forwarder:
 * return winsock_process_error(wsf(a1,a2,a3,a4), a1, a2, a3, a4);
 * wsf = fn ptr in ?ws@@3U_winsock_funcs@@A+0xe (call ds:[ws+0xe], cdecl).
 * The 4 arg pushes for the ws call double as winsock_process_error's
 * args 2..5 (push order a4,a3,a2,a1 then result; add esp,0x14).
 */
extern char *(*w31g_wsf)(char *, int, char *, int);
extern char *w31g_wproc(int, char *, char *, int);

char *__cdecl w31g_wsockerr(char *a1, int a2, char *a3, int a4)
{
    return w31g_wproc(w31g_wsf(a1, a2, a3, a4), a1, a2, a3, a4);
}
