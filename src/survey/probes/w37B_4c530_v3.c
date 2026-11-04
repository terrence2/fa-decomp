/* w37B 0x4c530 (rva 312624, 144 B) @FortMultiButtonText2@8 v3. FA layout
 * facts: result-clone `fmt` spilled FIRST (slot1 [esp+0x14] = 89 44 24 14
 * right after the fmtfn call), q = slot0 (flag [esp+0x13]); i = ESI
 * (33 f6 AFTER the *list early-return test), list = EDI (8b fa), mv = EBP,
 * p = ecx; final: FortMultiButton2(edx=i, ecx=ebp = mv); MMFreePtr(ecx =
 * [esp+0x14] = the result clone); 2x 8d 64 24 00 lea-pad tail. v2 had
 * CL spinning mv to a slot and psav to ebp — invert by declaring fmt
 * first and not cloning mv. */
extern int strcmp(const char *, const char *);
extern char *__fastcall w37b_ffmtX(void *mv, char *flagout);   /* $FA$_t_44c5c0 */
extern char *__fastcall NextString(char *s, long step);         /* @NextString@8 */
extern void __fastcall FortMultiButton2(void *mv, long idx);    /* @FortMultiButton2@8 */
extern void __fastcall MMFreePtr(void *p);                      /* @MMFreePtr@4 */

struct W37BFlag2 { char pad[3]; char flag; };

void __fastcall FortMultiButtonText2(void *mv, char *list)
{
    char *fmt;
    struct W37BFlag2 q;
    long i = 0;
    char *p;

    if (*list == 0)
        return;
    p = fmt = w37b_ffmtX(mv, &q.flag);
    for (;;) {
        if (!*p) {
            i = 0;
            break;
        }
        if (strcmp(p, list) == 0)
            break;
        p = NextString(p, (i++, 1));
    }
    FortMultiButton2(mv, i);
    if (q.flag)
        MMFreePtr(fmt);
}