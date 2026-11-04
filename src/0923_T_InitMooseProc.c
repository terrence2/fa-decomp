extern unsigned char desertMap[];
extern unsigned char makeTargetList[];
extern void __fastcall farmProc_(int ctx);
void T_InitMooseProc(void)
{
    if (desertMap[0])
        farmProc_((int)(makeTargetList + 0x1580));
    else
        farmProc_((int)(makeTargetList + 0x12a8));
}
