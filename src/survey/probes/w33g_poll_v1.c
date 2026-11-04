/* rva 0x1f340 (127808), 48 B - poll loop: while (n2(n1())) cnt++ */
extern int  w33g_n1(void);             /* -> $FA$_t_41f280 */
extern char __fastcall w33g_n2(int);   /* -> $FA$_t_41f320 */
extern int  w33g_ocnt;                 /* -> ?janesOnlineName@@3PADA+0xb8 */

void w33g_poll(void)
{
    while (w33g_n2(w33g_n1()))
        w33g_ocnt++;
}
