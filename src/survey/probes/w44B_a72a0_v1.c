/* rva 0xa72a0 (dec 684704), size 0x60 (84 code B + 12 filler).
 * __fastcall: ecx = total ptr, edx = deep ptr. Zeroes both, then loops i
 * from 0
 * while [0x573e60] > i over 22-B records at *(0x505f98)+i*0x16:
 *   word[r] != 0xffff, byte[r+0x15] != 0xff -> total++
 *   byte[r+0x15] == 0xff, word[r+0xe] & 4   -> total++
 *   byte[r+0x15] == 0xff, word[r+0xe] & 4==0-> deep++; total++
 * FA reloads the record pointer from memory EVERY iteration (volatile),
 * holds 0xff in ebx and 4 in ebp, keeps the i*0x16 offset in edi.
 */
extern int w44B_acnt;                  /* _PLcanardPosZ-0x4 @0x573e60 */
extern unsigned char * volatile w44B_rbase;   /* _hackSky-0x8 @0x505f98 */

int __fastcall w44B_scanrec(int *total, int *deep)
{
    unsigned long off = 0;
    unsigned char ff = 0xff;
    unsigned short m4 = 4;
    *deep = 0;
    *total = 0;
    {
        int i;
        for (i = 0; *(volatile int *)&w44B_acnt > i; i++) {
            unsigned char *r = w44B_rbase + off;
            if (*(unsigned short *)r != 0xffff) {
                if (*(unsigned char *)(r + 0x15) != ff) {
                    (*total)++;
                } else if (*(unsigned short *)(r + 0xe) & m4) {
                    (*total)++;
                } else {
                    (*deep)++;
                    (*total)++;
                }
            }
            off += 0x16;
        }
    }
    return *total;
}