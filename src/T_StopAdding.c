// _T_StopAdding@0 @ rva 0xc23d0 — guards curScreen != 3 then tail-jmps to
//   _OBJFindHumans@0 (probe d86 exact; __stdcall decls for the @0 symbols).
extern short curScreen;
extern void __stdcall OBJStopAdding(void);
extern void __stdcall OBJFindHumans(void);

void T_StopAdding_q(void)
{
    if (curScreen != 3) OBJStopAdding();
    OBJFindHumans();
}
