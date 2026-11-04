// __CallSettingFrame@12 @ rva 0xd9050 (37 B, gap chunk) — CRT EH
// setjmp-on-unwind trampoline: stash DispatcherContext+0xc (ScopeIndex
// field) in the ebp-4 slot, push TargetFrame/TargetIp args, move
// ScopeIndex into ebp and TargetIp into ecx, call __NLG_Notify1 (which
// pushes the NLG dword and chains into __NLG_Return), then call eax
// (the TargetIp/entry the dispatcher handed us — ff d0 is the chunk's
// last 2 bytes; this frame never returns here).
extern void csfNotify(void);

void __declspec(naked) CallSettingFrame_q(void)
{
    __asm {
        push ebp
        mov  ebp, esp
        sub  esp, 4
        push ebx
        push ecx
        mov  eax, dword ptr [ebp+0xc]
        add  eax, 0xc
        mov  dword ptr [ebp-4], eax
        mov  eax, dword ptr [ebp+8]
        push ebp
        push dword ptr [ebp+0x10]
        mov  ecx, dword ptr [ebp+0x10]
        mov  ebp, dword ptr [ebp-4]
        call csfNotify
        call eax
    }
}