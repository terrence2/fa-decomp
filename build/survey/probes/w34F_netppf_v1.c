typedef void (__cdecl *CBPF)(void *, int, char *, char *, int);
extern CBPF w34f_cb1;
extern CBPF w34f_cb2;
extern void *w34f_cbdat;
extern unsigned char w34f_plist[];

void __cdecl w34f_netppf(int p1, char *s)
{
    if (w34f_cb1 == 0)
        return;
    w34f_cb2(w34f_cbdat, 0, s, (char *)*(char **)(w34f_plist + p1 * 4) + 0x70, 0);
}