// @MAPObjAlts@4 @ rva 0x21d10 (96 B) — v2: (a) save declared long so the
//   load is 0f bf 35 movsx; (b) byte copy c = p after the global pair so the
//   test rides on bl.
extern short w27c_malt;             /* =_mainV+0x8c */
extern void __fastcall w27c_alt2(char a, int b);   /* =$FA$_t_421d70 */

void __fastcall w27c_MAPObjAlts(unsigned char p)
{
    long save;
    unsigned char c;
    save = w27c_malt;
    w27c_malt = 1;
    c = (unsigned char)p;
    if (c) {
        w27c_alt2(c, 1);
        w27c_alt2(c, 0);
        w27c_malt = save;
        return;
    }
    w27c_alt2(c, 0);
    w27c_alt2(c, 1);
    w27c_malt = save;
}
