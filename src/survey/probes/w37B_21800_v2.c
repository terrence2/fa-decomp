/* w37B 0x21800 (rva 137216, 128 B) _ZONEForGV@0 v2. Same as v1 but the
 * InBounds3 arg1 is spelled &w37b_ct11X (an extern char OBJECT at
 * _curThing+0x11) so CL emits FA's exact 68-imm32 push (push offset)
 * instead of a1+50. Everything else identical to v1 which was 1 B long
 * for exactly that reason. */
extern short w37b_zcntX;      /* ?cobraData@@3UGlobalData@@A+0xc1c0 */
extern char w37b_zones[];     /* ?cobraData@@3UGlobalData@@A+0xc1c8 */
extern char w37b_ct9X;        /* _curThing+0x9 */
extern char w37b_ct11X;       /* _curThing+0x11 (object; & it) */
extern char __fastcall w37b_zfnX(char *z);              /* $FA$_t_421880 */
extern char __stdcall InBounds3(void *a, void *b);      /* _InBounds3@8 */

void *__stdcall ZONEForGV(void)
{
    char *p;

    p = w37b_zones;
    while (p < w37b_zones + (long)w37b_zcntX * 46) {
        if (!w37b_zfnX(p))
            continue;
        if (p[0xc] != 4)
            continue;
        if ((p[0x27] ^ w37b_ct9X) & 0x80)
            continue;
        if (InBounds3(&w37b_ct11X, p))
            return p;
        p += 46;
    }
    return 0;
}