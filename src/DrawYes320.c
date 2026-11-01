// _DrawYes320 @ rva 0x8ad40 (48 B) — shell-alloc-wrapped 320-dialog yes
// button:
//   call PushShellAlloc / mov eax,[esp+4] / push eax / push 0x8004 /
//   push <imm _checkRightButton+0x3e8> / call RMAccessHandle@8 / push eax /
//   call Do320Button / jmp PopShellAlloc
// The pushed param stays on the stack through RMAccessHandle (@8 pops only
// its two args) and becomes Do320Button's arg2; right-to-left C pushes the
// resource id first (mov eax,[esp+4]/push eax) then 0x8004 then the id
// address (probe w13a_drawyes exact outside reloc dwords). The tail jmp is
// CL's 0-arg void tail-jmp (w8_i24 precedent).
extern void __stdcall PushShellAlloc(void);
extern void __stdcall PopShellAlloc(void);
extern long __stdcall RMAccessHandle(long id, long flags);
extern void __stdcall Do320Button(long h, void *action);
extern char drawYesRes[];      // _checkRightButton+0x3e8 (resource)

void DrawYes320(void *action)
{
    PushShellAlloc();
    Do320Button((long)RMAccessHandle((long)drawYesRes, 0x8004), action);
    PopShellAlloc();
}