// @MAPObjAlts@4 @ rva 0x21d10 (96 B) — v3: comma-guard forces FA order:
//   save = g / if (g = 1, c = p) so the g-store precedes the bl test.
extern short w27c_malt;             /* =_mainV+0x8c */
extern void __fastcall w27c_alt2(char a, int b);   /* =$FA$_t_421d70 */

void __fastcall w27c_MAPObjAlts3(unsigned char p)
{
    long save;
    unsigned char c;
    save = w27c_malt;
    if (w27c_malt = 1, c = (unsigned char)p) {
        w27c_alt2(c, 1);
        w27c_alt2(c, 0);
        w27c_malt = save;
        return;
    }
    w27c_alt2(c, 0);
    w27c_alt2(c, 1);
    w27c_malt = save;
}
