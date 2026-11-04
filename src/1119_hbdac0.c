/* w41E_bdac0_v1: nameless 64-B chunk @ 0xbdac0 (VA 0x4bdac0), fpo/esp,
 * no prolog, no params; twin of w35D_bd9d0 (CreateMove wrapper band).
 * FA body: CreateMove((char*)_curThing+0x38, 0, 1,
 *   movsx-word [_curThing+0x1d], 1, movsx-word [+0x1f], 1,
 *   movsx-word [+0x21], 1, 0, 8, 0x10, 0x7fff); 13-arg stdcall.
 * FA abs fixup dwords (HIGHLOW): movsx disps 0xa/0x15/0x1c + push imm 0x2f
 * -> CL's extern-array addressing gives the same HIGHLOWs via addend disp.
 */
extern unsigned char w41e_ct[0x1000];
/* map _w41e_ct=_curThing */
extern long __stdcall CreateMove(long a1, long a2, long a3, long a4, long a5,
                                 long a6, long a7, long a8, long a9, long a10,
                                 long a11, long a12, long a13);

void __cdecl w41e_bdac0(void)
{
    CreateMove((long)(w41e_ct + 0x38), 0, 1,
               (long)(short)*(unsigned short *)(w41e_ct + 0x1d), 1,
               (long)(short)*(unsigned short *)(w41e_ct + 0x1f), 1,
               (long)(short)*(unsigned short *)(w41e_ct + 0x21), 1,
               0, 8, 0x10, 0x7fff);
}