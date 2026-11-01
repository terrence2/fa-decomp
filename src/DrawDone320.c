// _DrawDone320 @ rva 0x8add0 (48 B) — DrawYes320 twin with resource id
// _checkRightButton+0x410 (probe form identical, w13a_drawyes).
extern void __stdcall PushShellAlloc(void);
extern void __stdcall PopShellAlloc(void);
extern long __stdcall RMAccessHandle(long id, long flags);
extern void __stdcall Do320Button(long h, void *action);
extern char drawDoneRes[];     // _checkRightButton+0x410 (resource)

void DrawDone320(void *action)
{
    PushShellAlloc();
    Do320Button((long)RMAccessHandle((long)drawDoneRes, 0x8004), action);
    PopShellAlloc();
}