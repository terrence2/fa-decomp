/* w38C 0x1f380 (144 B) @FortMultiButtonText@8 v2: adapted w37B_2e1c0_v3
 * + empty-list early-out (mov al,[edx] before prolog), i=EDI plan. */
extern char *__fastcall w38c_ffmtX(void *mv, char *flagout); /* $FA$_t_41f410 */
extern char *__fastcall w38c_nextstr(char *s, long step);    /* @NextString@8 */
extern void __fastcall w38c_fmb(void *mv, long idx);         /* @FortMultiButton@8 */
extern void __fastcall w38c_mmfree(void *p);                 /* @MMFreePtr@4 */
extern int strcmp(const char *, const char *);

struct W38CFlag { char pad[3]; char flag; };

void __fastcall FortMultiButtonText(void *mv, char *list)
{
    struct W38CFlag q;
    char *psav;
    char *p;
    long i = 0;

    if (!*list)
        return;
    p = psav = w38c_ffmtX(mv, &q.flag);
    for (;;) {
        if (!*p) {
            i = 0;
            break;
        }
        if (strcmp(p, list) == 0)
            break;
        p = w38c_nextstr(p, (i++, 1));
    }
    w38c_fmb(mv, i);
    if (q.flag)
        w38c_mmfree(psav);
}