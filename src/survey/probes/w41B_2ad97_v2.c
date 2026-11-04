/* w41B 0x2ad97 v2: pred takes the wc value (fastcall arg in ecx); zero
 * local declared after idx (FA: mov ecx,[wc] / xor esi,esi / test ecx). */
extern void *specials[];   /* _specials */
extern char w41bWc[];      /* -> ?worldCenter@@3UF24_POINT3@@A+0x10 */
extern char __fastcall w41bPred(long w);       /* -> $FA$_t_423dd0 */
extern void w41bClrScales(void);  /* -> $FA$_t_422368 */
extern long __fastcall MMFreePtr(void *p);   /* -> @MMFreePtr@4 */

void w41bClearSpecial(void)
{
    long idx = *(long *)w41bWc;
    long zero = 0;
    if (idx) {
        if (w41bPred(idx)) {
            MMFreePtr(specials[*(long *)w41bWc]);
            idx = *(long *)w41bWc;
            specials[idx] = (void *)zero;
            w41bClrScales();
        }
    }
}