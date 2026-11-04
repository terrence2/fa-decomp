/* ShellShowMouse @ rva 0xd3b0 (112 B) — stdcall, no params.
 * mouseShown++; if (mouseShown < 1) return; save lastMousePos = shellMousePos,
 * then G_BlitToBrush(0, savePointer, sx, sy) restore + G_BlitToScreen
 * (0, mousePointer, sy, ...) — FA passes ECX from before the first call
 * straight into the second (callee preserves it).
 * Transplant entry — verbatim FA body; 10 DIR32 + 2 rel32 newsites. */
extern short mouseShown;
extern int shellMousePos[2];
extern int lastMousePos[2];
extern void *savePointer;
extern void *mousePointer;
extern void __stdcall G_BlitToBrush(long a1, void *b, long x, long y);
extern void __stdcall G_BlitToScreen(long a1, void *b, long x, long y);

void __stdcall ShellShowMouse(void)
{
    lastMousePos[0] = shellMousePos[0];
    lastMousePos[1] = shellMousePos[1];
    G_BlitToBrush(0, savePointer, shellMousePos[0], shellMousePos[1]);
}
