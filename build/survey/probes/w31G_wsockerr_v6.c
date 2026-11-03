/* v6: fn ptr as a packed struct member (ws.err) — probe whether a member
 * fn-ptr call makes CL share the 4 arg slots with the outer call */
#pragma pack(push, 1)
struct W31G_WSFN { unsigned long pad[3]; unsigned short pad2;
                   char *(*err)(char *, int, char *, int); };
#pragma pack(pop)
extern struct W31G_WSFN w31g_wsx;   /* ?ws@@3U_winsock_funcs@@A */
extern char *w31g_wproc(int, char *, char *, int);

char *__cdecl w31g_wsockerr(char *a1, int a2, char *a3, int a4)
{
    return w31g_wproc(w31g_wsx.err(a1, a2, a3, a4), a1, a2, a3, a4);
}
