// _RestoreClip @ rva 0xd0c38 (12 B, gap chunk) — loads the gouraudOn+0x11d
// flag byte into AL (a0 moffs — MASM's direct-memory-to-AL form) and tail
// calls check_flat+0x2d0 (chunk-interior target: callee takes the flag in
// AL, unrepresentable in C) then ret. Addend lives ONLY in the maps
// (wave-12 double-addend rule): the C/asm refs are the bare externs.
extern char gouraudOn[];
extern void restoreClipCallee(void);

void __declspec(naked) RestoreClip(void)
{
    __asm {
        mov  al, byte ptr gouraudOn
        call restoreClipCallee
        ret
    }
}