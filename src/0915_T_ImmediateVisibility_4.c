/* v2 — adds the leading memcpy(w44B_v, obj, 0xc0); call #3's result is
 * NOT tested in FA (plain statement call). FA interleaves InBounds's
 * arg2 push between the copy setup and rep movsd; toolchain-diff bands
 * handle that, the prolog push ebx/mov esi=ebx and pop ebx, and the
 * call disp literals (all FA call rel32s are baked, no .reloc entries).
 */
extern unsigned char w44B_v[];       /* _v @0x56a458 */
extern unsigned char w44B_curH[];    /* curThing @0x508738 */
extern unsigned char w44B_curA[];    /* curThing+0x11 @0x508749 */
extern unsigned long w44B_t1;        /* curThing+0x1 @0x508739 */
extern unsigned short w44B_curA2;    /* curThing+0x6a @0x5087a2 */
extern unsigned short curId;         /* 0x4f2f24 */
extern unsigned short currentT;      /* 0x549e18 */
extern int __stdcall InBounds(int, int);
extern char __fastcall w44B_visf(void *, unsigned short);
extern void __fastcall w44B_visf2(unsigned short, unsigned long, int);
extern void *memcpy(void *, const void *, unsigned long);

void __stdcall T_ImmediateVisibility(unsigned char *obj)
{
    memcpy(w44B_v, obj, 0xc0);
    if (!InBounds(w44B_curA, w44B_v + 0x42))
        goto end;
    if (!w44B_visf(w44B_curH, (unsigned short)curId))
        goto end;
    w44B_visf2((unsigned short)curId, 0, 1);
    if (*(volatile unsigned long *)&w44B_t1 & 2)
        *(volatile unsigned short *)&w44B_curA2 = currentT + 0x14;
end:
    memcpy(obj, w44B_v, 0xc0);
}