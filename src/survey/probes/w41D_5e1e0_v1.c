/* w41D 0x5e1e0 (64 B, tail 90) — WNG-band vertical-spacing apply (SpacingV
 * recipe verbatim, callee _WNGPart@12): mov ax[curId]/push 0/66 89 0d
 * <curThing+0xff> (word store, fastcall vv in cx)/push 0/push eax/
 * call _WNGPart@12/cmp al,1/jne; MSGSend(curId,0x8001,0,0,0x8000,8,
 * curThing+0xff,2).  Proven plain-C shape: src/GRPSetSpacingV.c EXACT
 * (store-first scheduling reproduces FA's mov-ax; store; 6a00 interleave).
 * Caller src/CTDo_wm_vspacing.c declares void __fastcall ctVsSp(int v).
 */
extern char curThing[];
extern unsigned short curId;

extern char __stdcall WNGPart(short a, int b, int c);
extern void __stdcall MSGSend(short id, int a, int b, int c, int d, int e,
                              void *ptr, int f);

void __fastcall w41D_5e1e0(short vv)
{
    *(short *)(curThing + 0xff) = vv;
    if (WNGPart(curId, 0, 0) == 1)
        MSGSend(curId, 0x8001, 0, 0, 0x8000, 8, curThing + 0xff, 2);
}