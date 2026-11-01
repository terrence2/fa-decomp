// _DrawNo320 @ rva 0x8ad70 (48 B) — DrawYes320 twin with resource id
// _checkRightButton+0x3f4 (probe form identical, w13a_drawyes).
extern void __stdcall PushShellAlloc(void);
extern void __stdcall PopShellAlloc(void);
extern long __stdcall RMAccessHandle(long id, long flags);
extern void __stdcall Do320Button(long h, void *action);
extern char drawNoRes[];       // _checkRightButton+0x3f4 (resource)

void DrawNo320(void *action)
{
    PushShellAlloc();
    Do320Button((long)RMAccessHandle((long)drawNoRes, 0x8004), action);
    PopShellAlloc();
}