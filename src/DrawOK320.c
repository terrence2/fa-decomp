// _DrawOK320 @ rva 0x8ae00 (48 B) — PushShellAlloc; then Do320Button(
// RMAccessHandle("OK320.PIC" @ _checkRightButton+0x41c, 0x8004), action); tail
// jmp PopShellAlloc. FA pushes the ACTION* arg first (mov eax,[esp+4]/push
// eax), then RMAccessHandle's 0x8004 + name, and after its 8-byte stdcall
// cleanup the handle result lands directly above the saved ACTION*: plain
// right-to-left C (probe w13b_DrawOK320).
extern void __stdcall PushShellAlloc_x(void);
extern void __stdcall PopShellAlloc_x(void);
extern void __stdcall Do320Button(void *h, void *a);
extern int __stdcall RMAccessHandle(int a, int b);
extern char ok320PicName[];

void DrawOK320(void *action)
{
    PushShellAlloc_x();
    Do320Button((void *)RMAccessHandle((int)ok320PicName, 0x8004), action);
    PopShellAlloc_x();
}