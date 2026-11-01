// _SetFlowControlThreshold@12 @ rva 0xd3600 (6 B) — SetFlowControlThreshold serial/modem comm-driver import pass-through thunk (FA.SMS imp stub).
extern void *impSetFlowControlThreshold[];
unsigned long __declspec(naked) __stdcall SetFlowControlThreshold(void *a0, void *a1, void *a2)
{
    __asm { jmp dword ptr [impSetFlowControlThreshold] }
}
