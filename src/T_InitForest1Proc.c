extern unsigned char desertMap[];
extern unsigned char makeTargetList[];
extern void __fastcall farmProc_(int ctx);
void T_InitForest1Proc(void)
{
    if (desertMap[0])
        farmProc_((int)(makeTargetList + 0x898));
    else
        farmProc_((int)(makeTargetList + 0x6d8));
}
