/* w36E e3d00 - tzset-style lazy init guard, 46B code + 4B cc census tail */
extern void w36e_lock(int);        /* __lock  0x4d7170 */
extern void w36e_unlock(int);      /* __unlock 0x4d71e0 */
extern void w36e_tzinner(void);    /* $FA$_t_4e3d60 */
extern long w36e_tzf;              /* __tzname+0x2c */
extern long w36e_tzf2;             /* __tzname+0x2c (2nd site) */
extern long w36e_tzf3;             /* __tzname+0x2c (inc site) */

void w36e_e3d00(void) {
    if (w36e_tzf == 0) {
        w36e_lock(11);
        if (w36e_tzf2 == 0) {
            w36e_tzinner();
            w36e_tzf3 = w36e_tzf3 + 1;
        }
        w36e_unlock(11);
    }
}
