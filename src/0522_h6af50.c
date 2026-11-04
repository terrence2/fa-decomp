/* FA 0x6af50 (80 B, fpo, no locals): cobra key/pause poll.
 * cobraKeyFlag=0; k=GetKey(); if (k==0x20 || k==0x1b || cobraATQuit)
 * flag=1; if (mouseButtonPresses[0] || mouseButtonPresses[1]) flag=1;
 * return (char)cobraKeyFlag.
 * FA shapes: c7 05 imm32 store; call GetKey; 66 3d 2000 cmp ax,0x20 (k short);
 * 66 3d 1b00; mov al,[cobraATQuit] test al,al je (load-test-store chain);
 * c7 05 flag,1; a0 moffs al loads of both mouseButtonPresses[0]/[1] (const
 * index folded into moffs); a0 mov al,[cobraKeyFlag] epilog.
 */
extern long cobraKeyFlag;
extern char cobraATQuit;
extern char mouseButtonPresses[];
extern short GetKey(void);

char w45E_6af50_v1(void)
{
    short k;

    cobraKeyFlag = 0;
    k = GetKey();
    if (k == 0x20 || k == 0x1b || cobraATQuit)
        cobraKeyFlag = 1;
    if (mouseButtonPresses[0] || mouseButtonPresses[1])
        cobraKeyFlag = 1;
    return (char)cobraKeyFlag;
}