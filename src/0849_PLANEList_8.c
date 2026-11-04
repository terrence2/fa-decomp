/* _PLANEList@8 @ rva 0x9dac0 (112 B) -- v2 = v1 with __stdcall (FA is
 * _PLANEList@8: ret 8; v1 was cdecl, lost 'c2 08 00' + one push). */
extern short numPlanes;         /* count, short (movswl read) */
extern short planes[];          /* base = 0x5688f8 */
extern char *objPtrs[];
extern char __stdcall w37c_inb9(char *p, long q);

void __stdcall w37c_planelist(long a1, char (__cdecl *cb2)(unsigned short))
{
    unsigned long one = 1;
    unsigned short *pw;
    char *o;

    pw = &planes[numPlanes - 1];
    while ((unsigned long)pw >= (unsigned long)planes) {
        o = objPtrs[*pw];
        if (*(long *)(o + 1) & one) {
            if (w37c_inb9(o + 0x11, a1)) {
                if (!cb2(*pw))
                    return;
            }
        }
        pw--;
    }
}