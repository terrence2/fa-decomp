/* FA 0x4222ed @MAPMaybeClearSelWP@8 (123 B) v2: offset counter + walker, common specC8 tail */
struct MAPWP { unsigned char f0; unsigned char pad[67]; };
extern long dms18[];            /* _desiredMapScale+0x18 */
extern long specC8[];           /* _specials+0xc8 */
extern void __stdcall wpq(long *out, long zero, struct MAPWP *node); /* $FA$_t_421cd0 */
extern void w43E_wpclr(void);   /* $FA$_t_422368 */

void __fastcall MAPMaybeClearSelWPQ(struct MAPWP *sel, struct MAPWP *wp)
{
    long a, b;
    long off, walker;

    if (*(unsigned char *)sel & 2)
        return;
    off = 0;
    walker = (long)sel;
    for (;;) {
        if (walker == *(long *)dms18)
            break;
        walker += 0x44;
        off += 0x44;
        if (*(unsigned char *)walker & 2)
            return;
    }
    wpq(&a, 0, sel);
    wpq(&b, 0, wp);
    if (b != a) {
        w43E_wpclr();
        *(long *)specC8 = 0;
        return;
    }
    *(long *)dms18 = (*(long *)dms18 - (long)sel) / 68 * 68 + (long)wp;
    *(long *)specC8 = 0;
}