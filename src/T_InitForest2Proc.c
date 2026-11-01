extern unsigned char desertMap[];
extern unsigned char makeTargetList[];
extern void __fastcall farmProc_(int ctx);
void T_InitForest2Proc(void)
{
    if (desertMap[0])
        farmProc_((int)(makeTargetList + 0xd60));
    else
        farmProc_((int)(makeTargetList + 0xab8));
}
