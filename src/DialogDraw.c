// ?DialogDraw@@YGXPAX@Z @ rva 0x86590 (32 B) — naked asm escape. FA asm:
//   call PushShellAlloc / mov ecx,[esp+4] / mov eax,[ecx+6] / test eax,eax /
//   je skip / push ecx / call eax / add esp,4 / skip: call PopShellAlloc / ret 4
// Calls the dialog's draw fn-ptr at [p+6] (dword at a 2-aligned odd offset)
// between the shell-alloc pair. C rounds 1-3 lost: CL's register plan is
// p->eax / fp->ecx (85 c9 test + ff d1 call + push eax), FA's plan is
// p->ecx (call-arg staging) / fp->eax (indirect call target, 85 c0 / ff d0 /
// push ecx) — probe variants v2 (esi/edi wilder) and v3 (ternary) keep CL's
// plan, no C steering found, so whole-body naked asm (probe
// b18c_DialogDraw4 exact). Mapped externs: _PushShellAlloc@0 /
// _PopShellAlloc@0 -> mangled shell chunks.
extern void __stdcall PushShellAlloc(void);
extern void __stdcall PopShellAlloc(void);

void __declspec(naked) __stdcall DialogDraw(void *p)
{
    __asm
    {
        call PushShellAlloc
        mov ecx, [esp+4]
        mov eax, [ecx+6]
        test eax, eax
        je skip
        push ecx
        call eax
        add esp, 4
skip:
        call PopShellAlloc
        ret 4
    }
}
