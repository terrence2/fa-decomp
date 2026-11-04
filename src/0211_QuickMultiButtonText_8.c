/* w37B 0x2e1c0 (rva 188864, 144 B) @QuickMultiButtonText@8 v3. FA layout
 * facts: mv-clone `fmt` spilled FIRST (slot1 [esp+4], store 89 4c 24 04 at
 * entry), q struct = slot0 (flag = [esp+0x13]); i = EDI, list = ESI;
 * psav (the fmtfn result for MMFreePtr) = ebp; p in ecx (volatile, the
 * inline-strcmp works straight off ecx/esi holders). v2 had decl order
 * inverted (q first -> CL put q@slot1/fmt@slot0, flag lea 0x17) and the
 * final call args swapped. v3: fmt decl first, q second, call
 * QuickMultiButton(fmt, i). */
extern int strcmp(const char *, const char *);
extern char *__fastcall w37b_qfmtX(void *mv, char *flagout); /* $FA$_t_42e250 */
extern char *__fastcall NextString(char *s, long step);      /* @NextString@8 */
extern void __fastcall QuickMultiButton(void *mv, long idx); /* @QuickMultiButton@8 */
extern void __fastcall MMFreePtr(void *p);                   /* @MMFreePtr@4 */

struct W37BFlag { char pad[3]; char flag; };

void __fastcall QuickMultiButtonText(void *mv, char *list)
{
    char *fmt = mv;
    struct W37BFlag q;
    long i = 0;
    char *psav;
    char *p;

    p = psav = w37b_qfmtX(fmt, &q.flag);
    for (;;) {
        if (!*p) {
            i = 0;
            break;
        }
        if (strcmp(p, list) == 0)
            break;
        p = NextString(p, (i++, 1));
    }
    QuickMultiButton(fmt, i);
    if (q.flag)
        MMFreePtr(psav);
}