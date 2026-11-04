/* w41B 0x21060 v2: do-while loops (FA enters on the load, bound check at
 * the bottom, no entry check). */
extern char w41bFs[];   /* -> _fortSizes+0xc8 */
extern char w41bFe[];   /* -> _fortSizes+0xdc */
extern char w41bIx[];   /* -> _fortSizeIndex+0x8 */
extern char w41bIe[];   /* -> _fortSizeIndex+0x1c */

int __fastcall w41bCoinFind(int key)
{
    long *p;
    p = (long *)w41bFs;
    do {
        if (*p == key)
            return 21;
        p = p + 1;
    } while (p < (long *)w41bFe);
    p = (long *)w41bIx;
    do {
        if (*p == key)
            return 25;
        p = p + 1;
    } while (p < (long *)w41bIe);
    return 0;
}