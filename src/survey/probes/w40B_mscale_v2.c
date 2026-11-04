/* rva 0x260cb (dec 155851), 52 B unnamed fastcall - map-scale setter.
 * v2: __fastcall (v1 lacked it, CL emitted cdecl) + goto-shared-exit
 * (FA: two jmp to a single pop edi/pop esi/ret 4 epilog).
 */
extern unsigned short w40b_msw1;   /* -> _desiredMapScale+0x4 */
extern unsigned long w40b_msl2;    /* -> _desiredMapScale+0x18 */
extern unsigned long w40b_wcx;     /* -> ?worldCenter@@3UF24_POINT3@@A+0x10 */
void w40b_rst(void);               /* -> $FA$_span_022368 / $FA$_t_422368 */

void __fastcall w40b_msc0(unsigned short w, unsigned long s, void *p)
{
    w40b_rst();
    if (w != 0)
        w40b_msw1 = w;
    else {
        if (s == 0) {
            w40b_wcx = (unsigned long)p;
            goto exit;
        }
        w40b_msl2 = s;
        goto exit;
    }
exit:;
}