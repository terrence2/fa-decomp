/* _AllocCmdBuf@0 @ 0x62ec0 (64 B)
   FA: call _CancelCmdBuf@0; a1 cmdBuf; test; jne past-call+store;
   xor ecx,ecx; mov edx,0x8080; mov cx,[_curThingType+0x5b]; call
   @MMAllocPtr@8; a3 cmdBuf; word cmdBufW=0; a1 cmdBuf reload; a3 chainPos;
   ret; pad 8d9b00000000 (6 B).
   MMAllocPtr@8 = fastcall; arg1 = zero-extended WORD at _curThingType+0x5b
   (xor ecx,ecx + mov cx). cmdBuf volatile: skip path must not fold the a3
   store and chainPos must reload. */
extern void * volatile cmdBufQ;     /* -> _curThing+0x5e */
extern unsigned short cmdBufW;      /* -> _curThing+0x62 */
extern void *chainPos20;            /* -> ?correctChainPlacement@@3DA+0x20 */
extern void __fastcall CancelCmdBuf(void);
extern unsigned long __fastcall MMAllocPtr_q(unsigned short cb, unsigned long x);
extern unsigned char thingTypeQ[];  /* -> _curThingType */

void __fastcall AllocCmdBuf(void)
{
    CancelCmdBuf();
    if (cmdBufQ == 0)
        cmdBufQ = MMAllocPtr_q((unsigned long)*(unsigned short *)(thingTypeQ + 0x5b), 0x8080);
    cmdBufW = 0;
    chainPos20 = cmdBufQ;
}