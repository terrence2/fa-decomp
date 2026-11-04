/* w36E be330 v2 - shared dac0 tail-jmp block via goto */
extern unsigned long w36e_fl;      /* = _curThingType+0xa6 */
extern unsigned long w36e_fl2;     /* = _curThingType+0xa6 (2nd site) */
extern unsigned short w36e_ws;     /* = _curThing+0xe4 */
extern void w36e_t360(void);       /* = $FA$_t_4be360 */
extern void w36e_d9d0(void);       /* = $FA$_t_4bd9d0 */
extern void w36e_dac0(void);       /* = $FA$_t_4bdac0 */

void w36e_be330(void) {
    if (w36e_fl & 0x10) { w36e_t360(); return; }
    if (!(w36e_fl2 & 0x1)) goto Ldac0;
    if (w36e_ws != 0) { w36e_d9d0(); return; }
Ldac0:
    w36e_dac0();
}
