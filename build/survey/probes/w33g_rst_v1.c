/* rva 0x22368 (140136), 24 B - zero four globals (a 16-bit + three dwords). */
extern unsigned short w33g_z1;  /* -> _desiredMapScale+0x4 */
extern int w33g_z2;             /* -> _desiredMapScale+0x18 */
extern int w33g_z3;             /* -> ?worldCenter@@3UF24_POINT3@@A+0x10 */
extern int w33g_z4;             /* -> ?cobraData@@3UGlobalData@@A+0xc2e0 */

void w33g_rst(void)
{
    w33g_z1 = 0;
    w33g_z2 = 0;
    w33g_z3 = 0;
    w33g_z4 = 0;
}
