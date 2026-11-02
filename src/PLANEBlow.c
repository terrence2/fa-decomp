// PLANEBlow v3 — cast uchar t55 to unsigned long at the call site so CL
// zero-extends via 33 c0 a0 ... 50 (xor; mov al; push eax), matching FA.
extern void __stdcall RemoveCurObj_f(void);
extern unsigned short w27a_curIdI;
extern unsigned long w27a_thisComI;
extern unsigned char w27a_cThingT55;
extern char w27a_cThing11[];
extern void __stdcall GraphicAddExp_f(unsigned long comp, unsigned long ty,
                                      char *thing, unsigned short id,
                                      int a, int b, int c);
void w27a_pblow_q(void)
{
    RemoveCurObj_f();
    GraphicAddExp_f(w27a_thisComI, (unsigned long)w27a_cThingT55,
                    w27a_cThing11, w27a_curIdI, 1, 1, 1);
}
