// PLANEBlow — GRAPHICAddExp is stdcall (FA has no caller cleanup);
// _thisComputer is a dword value arg.
extern void __stdcall RemoveCurObj_f(void);           /* _RemoveCurObj@0 */
extern unsigned short w27a_curIdI;                    /* _curId */
extern unsigned long w27a_thisComI;                   /* _thisComputer */
extern unsigned char w27a_cThingT55;                  /* _curThingType+0x55 */
extern char w27a_cThing11[];                          /* _curThing+0x11 */
extern void __stdcall GraphicAddExp_f(unsigned long comp, unsigned char ty,
                                      char *thing, unsigned short id,
                                      int a, int b, int c);
                                                      /* _GRAPHICAddExp@28 */
void w27a_pblow_q(void)
{
    RemoveCurObj_f();
    GraphicAddExp_f(w27a_thisComI, w27a_cThingT55, w27a_cThing11,
                    w27a_curIdI, 1, 1, 1);
}
