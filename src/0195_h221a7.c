// $FA$_t_4221a7 @ rva 0x221a7 (24 B) — fly-handle cleanup: fastcall-free of
// the dword at ?mcFlyAll@@3DA+0x20, then stores 0 / byte-0 at +0x20/+0x24.
// FA: 8b 0d <imm> / e8 call / 33 c0 / a3 <imm> / a2 <imm> / c3 (no frame)
extern void __fastcall MMFreeHandle(int h);
extern int flyHnd;        /* ?mcFlyAll@@3DA+0x20 */
extern char flyAct;       /* ?mcFlyAll@@3DA+0x24 */

void w32d_closeFly(void)
{
    MMFreeHandle(flyHnd);
    flyHnd = 0;
    flyAct = 0;
}