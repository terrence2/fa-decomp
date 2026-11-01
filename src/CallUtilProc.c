// _CallUtilProc @ rva 0x63120 (64 B) — naked asm escape. FA asm:
//   mov eax,[esp+4] / push ebx / push eax / push OFFSET curThing /
//   call $FA$_t_4630f0 (2-arg stdcall helper at 0x4630f0, ret 8) /
//   test eax,eax / je null_ret (74 1b forward to the 0-exit at the end)
//   mov ecx,[esp+0x18] / mov edx,[esp+0x14] / mov ebx,[esp+0x10] / push ecx /
//   mov ecx,[esp+0x10] / push edx / push ebx / push ecx / call eax /
//   add esp,0x10 / pop ebx / ret
//   null_ret: 66 33 c0 (xor ax,ax) / pop ebx / ret
// Forwards msg `a` to the thing's util proc, calling proc(b,c,d,e) with the
// remaining four incoming params. C round 2 (ternary p ? p(...) : 0) reached
// FA's layout exactly EXCEPT the 0 arm: CL emits 33 c0; FA emits 66 33 c0
// (xor ax,ax with eax's uppers known-0 from the preceding test) — no int-
// return C form reaches it (wave-13 66 33 c0 family + int passthrough on the
// success path), so whole-body naked asm (probe b18c_CallUtilProc3 exact).
// Helper is unnamed in layout -> $FA$_t_4630f0 anchor map.
extern char curThing[];
extern long __stdcall utilProcLookup(long obj, long msg);

int __declspec(naked) __cdecl CallUtilProc(int a, int b, int c, int d, int e)
{
    __asm
    {
        mov eax, [esp+4]
        push ebx
        push eax
        push OFFSET curThing
        call utilProcLookup
        test eax, eax
        je null_ret
        mov ecx, [esp+0x18]
        mov edx, [esp+0x14]
        mov ebx, [esp+0x10]
        push ecx
        mov ecx, [esp+0x10]
        push edx
        push ebx
        push ecx
        call eax
        add esp, 0x10
        pop ebx
        ret
null_ret:
        xor ax, ax
        pop ebx
        ret
    }
}
