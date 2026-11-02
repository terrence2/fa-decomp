// _G_CircleFlip@16 @ rva 0x96770 (43 B code + 8 B 8d64x2 pad) — asm
// escape: plain C probe schedules _cb load first (8b 0d into ecx, then
// [ecx+6], sub from a stack read) while FA loads the d/c params first,
// pushes d, THEN loads _cb into edx (8b 15) and keeps c/b in stack
// reloads (8b 44 24 0c).  m = *(int*)((char*)_cb+6).
extern char* cb;                        /* _cb */
extern void __stdcall G_Circle(int a, int b, int c, int d);

__declspec(naked) void __stdcall G_CircleFlip_q(int a, int b, int c, int d)
{
    __asm {
        mov  eax, dword ptr [esp+10h]
        mov  ecx, dword ptr [esp+0Ch]
        push eax
        mov  edx, cb
        mov  eax, dword ptr [esp+0Ch]
        push ecx
        mov  ecx, dword ptr [edx+6]
        sub  ecx, eax
        mov  eax, dword ptr [esp+0Ch]
        dec  ecx
        push ecx
        push eax
        call G_Circle
        ret  10h
    }
}