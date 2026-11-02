/* v10: volatile-field spelling at /Os (size-lean). */
extern void __stdcall w28a_unin(void *a);   /* =_UnInitializePort@4 */
extern volatile unsigned long w28a_conn;    /* =?mpInfo@@3UMP_INFO@@C+0x154 */
extern volatile unsigned long w28a_conn2;   /* =?mpInfo@@3UMP_INFO@@C+0x160 */
extern volatile unsigned long w28a_state;   /* =?mpInfo@@3UMP_INFO@@C+0x16c */
extern void *w28a_cp;                       /* =?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */

void __cdecl w28a_SER_Shutdown3(void)
{
    unsigned long c = w28a_conn;
    unsigned long z = 0;
    if (c != z) {
        w28a_unin(w28a_cp);
        w28a_conn = z;
        w28a_conn2 = z;
        w28a_state = z;
    }
}
