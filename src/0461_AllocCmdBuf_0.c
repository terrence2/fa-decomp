extern void * volatile cmdBufQ;     /* -> _curThing+0x5e */
extern unsigned short cmdBufW;      /* -> _curThing+0x62 */
extern void *chainPos20;            /* -> ?correctChainPlacement@@3DA+0x20 */
extern void __fastcall CancelCmdBuf(void);
extern unsigned long __fastcall MMAllocPtr_q(unsigned long cb, unsigned long x);
extern unsigned char thingTypeQ[];  /* -> _curThingType */

void __fastcall AllocCmdBuf(void)
{
    CancelCmdBuf();
    if (cmdBufQ == 0)
        cmdBufQ = MMAllocPtr_q(*(unsigned short *)(thingTypeQ + 0x5b), 0x8080);
    cmdBufW = 0;
    chainPos20 = cmdBufQ;
}
