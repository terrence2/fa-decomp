// ?PLANEBlow@@YAXXZ @ rva 0x9b880 (48 B) — RemoveCurObj; args pushed
// 1,1,1,ax, then mov ecx,_thisComputer; push &_curThing+0x11; xor eax; mov
// al,_curThingType+0x55; push eax; push ecx; call _GRAPHICAddExp@28.
extern void __cdecl RemoveCurObj_f(void);                 /* _RemoveCurObj@0 */
extern unsigned short w27a_curIdI;                        /* _curId */
extern void *w27a_thisComI;                               /* _thisComputer */
extern unsigned char w27a_cThingT55;                      /* _curThingType+0x55 */
extern char w27a_cThing11[];                              /* _curThing+0x11 */
extern void __cdecl GRAPHICAddExp_f(void *comp, unsigned char ty, char *thing,
                                     unsigned short id, int a, int b, int c);
                                                          /* _GRAPHICAddExp@28 */
void w27a_pblow_q(void)
{
    RemoveCurObj_f();
    GRAPHICAddExp_f(w27a_thisComI, w27a_cThingT55, w27a_cThing11, w27a_curIdI,
                    1, 1, 1);
}