// 0xc55d4 NoHorizon (40 B) — naked-asm v1 (bx/dx 16-bit reg loads to the
// Horizon2d-interior helper are unspellable in plain C)
extern void NoHzF1(void);
extern void NoHzF2(void);
extern void GSetColorW(void);
extern char ltupT[];
extern char wtopT[];
extern char wbotT[];

__declspec(naked) void NoHorizon27(void)
{
    __asm {
        call NoHzF1
        movzx ecx, word ptr [ltupT]
        call GSetColorW
        mov bx, word ptr [wtopT]
        mov dx, word ptr [wbotT]
        call NoHzF2
        ret
    }
}