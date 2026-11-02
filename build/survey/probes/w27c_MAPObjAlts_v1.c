// @MAPObjAlts@4 @ rva 0x21d10 (138512, 96 B) — fastcall (ecx param):
//   push ebx / push esi / movsx esi,word [mainV+0x8c] / mov word [mainV+0x8c],1
//   / mov bl,cl / test / je L / mov edx,1 / mov ecx,ebx / call $FA$_t_421d70 /
//   xor edx,edx / mov ecx,ebx / call / mov word [mainV+0x8c],si / pop / ret
//   (both branches; tails duplicated).
extern short w27c_malt;             /* =_mainV+0x8c */
extern void __fastcall w27c_alt2(char a, int b);   /* =$FA$_t_421d70 */

void __fastcall w27c_MAPObjAlts(unsigned char p)
{
    short save = w27c_malt;
    w27c_malt = 1;
    if (p) {
        w27c_alt2(p, 1);
        w27c_alt2(p, 0);
        w27c_malt = save;
        return;
    }
    w27c_alt2(p, 0);
    w27c_alt2(p, 1);
    w27c_malt = save;
}
