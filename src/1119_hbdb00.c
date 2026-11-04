/* w41E_bdb00_v1: nameless 64-B chunk @ 0xbdb00 (VA 0x4bdb00), fpo/esp,
 * twin of 0xbdac0; middle words come from _sunAngle:
 *   movsx ecx,[ _sunAngle+2 ] (arg6), movsx edx,[ _sunAngle ] (arg4);
 * arg8 stays movsx-word [_curThing+0x21] (shared first movsx).
 */
extern unsigned char w41e_ct[0x1000];
/* map _w41e_ct=_curThing */
extern unsigned char w41e_sun[0x80];
/* map _w41e_sun=_sunAngle */
extern long __stdcall CreateMove(long a1, long a2, long a3, long a4, long a5,
                                 long a6, long a7, long a8, long a9, long a10,
                                 long a11, long a12, long a13);

void __cdecl w41e_bdb00(void)
{
    CreateMove((long)(w41e_ct + 0x38), 0, 1,
               (long)(short)*(unsigned short *)w41e_sun, 1,
               (long)(short)*(unsigned short *)(w41e_sun + 2), 1,
               (long)(short)*(unsigned short *)(w41e_ct + 0x21), 1,
               0, 8, 0x10, 0x7fff);
}