// ?ShellHideMouse@@YGXXZ @ rva 0xd420 — C v1
extern short mouseShownW;        /* ?mouseShown@@3FA */
extern short lastMX[];           /* ?lastMousePos@@3UWORD_POINT@@A+0x2 */
extern short lastMY[];           /* ?lastMousePos@@3UWORD_POINT@@A */
extern void *savePointerG;       /* ?savePointer@@3PAUT_HANDLE@@A */
extern void __stdcall G_BlitToScreenX(int, void *, int, int);

void __stdcall ShellHideMouse_q(void)
{
    if (++mouseShownW != 0)
        return;
    G_BlitToScreenX(0, savePointerG, lastMX[0], lastMY[0]);
}
