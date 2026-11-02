// _MOUSESetPos@8 @ rva 0x97d40 (39 B code + 9 B 8bff/8da424 pad) — centers
// the mouse: 0f bf 05 (movsx eax, ds:[_grMode+0xa]) / cdq / sub / sar /1 /
// 66 a3 (word moffs store) to _mousePos, then the +0xc twin into +0x2.
// params never read.  CL gives 66 89 05 modrm stores (7 B vs FA 5 B) —
// fitobj --patch shrinks both sites; grModeW/mpos0/mpos1 are interior
// human-coin maps.
extern short grModeW[];                 /* _grMode */
extern short mousePosQ0;                /* _mousePos */
extern short mousePosQ1;                /* _mousePos+0x2 */

void __stdcall MOUSESetPos_q(int a, int b)
{
    mousePosQ0 = grModeW[5] / 2;
    mousePosQ1 = grModeW[6] / 2;
}