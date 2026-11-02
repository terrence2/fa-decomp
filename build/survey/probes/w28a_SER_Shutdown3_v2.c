/* v2: chained assignment materializes the zero in esi (89 35 stores). */
extern void __stdcall w28a_unin(void *a);   /* =_UnInitializePort@4 */
extern unsigned long w28a_conn;             /* =?mpInfo@@3UMP_INFO@@C+0x154 */
extern unsigned long w28a_conn2;            /* =?mpInfo@@3UMP_INFO@@C+0x160 */
extern unsigned long w28a_state;            /* =?mpInfo@@3UMP_INFO@@C+0x16c */
extern void *w28a_cp;                       /* =?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */

void __cdecl w28a_SER_Shutdown3(void)
{
    unsigned long z;
    if (w28a_conn != 0) {
        w28a_unin(w28a_cp);
        w28a_conn = z = 0;
        w28a_conn2 = z;
        w28a_state = z;
    }
}
