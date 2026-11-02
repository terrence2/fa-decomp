// __ArmPlane@4 @ rva 0x7e910 (80 B) — byte _doArmPlane gate; else-path
//   cmp [p],1; sbb eax,eax; and 0xfffffffb; add 0x12 (ternary 13/18);
//   arm path: mov al,_pilotName; mov ecx,0; cmp al,1; adc ecx,-1;
//   and ecx,&_campaignPilot; call @ArmPlane@4 (short return, movsx eax,ax);
//   *p = (r == 0x12) via sete dl.
extern unsigned char w27a_dab;      /* _doArmPlane */
extern unsigned char w27a_pnB;      /* _pilotName */
extern void *w27a_cpP;              /* _campaignPilot */
extern short __fastcall ArmPlane_f(void *cp);    /* @ArmPlane@4 */
int __stdcall w27a_arm_q(unsigned char *p)
{
    short r;
    if (w27a_dab != 0)
    {
        r = ArmPlane_f(w27a_pnB != 0 ? &w27a_cpP : (void *)0);
        *p = (unsigned char)(r == 0x12);
        return r;
    }
    return (*p < 1 ? 13 : 18);
}