// ?WaitForVerticalBlank@CDirDraw@@QAEXK@Z @ rva 0x1dd70 (48 B) — thiscall
// member; DirectDraw WaitForVerticalBlank via vtable slot 0x58/4, retrying
// while DDERR_WASSTILLDRAWING (0x8876021c). FA: push ebx/esi/edi;
// eax=[ecx+0x280]; mov edi,ecx; test eax/eax; je exit; loop:
// esi=[esp+0x10](flags); eax=[edi+0x280]; push 0; ebx=[eax]; push esi;
// push eax; call [ebx+0x58]; cmp eax,0x8876021c; je loop. CL 4.2 C++ path
// for the exact QAEXK mangle.
class CDirDraw {
public:
    void WaitForVerticalBlank(unsigned long dwFlags);
};

typedef int (__stdcall *ddvbFunc)(void *, unsigned long, unsigned long);

void CDirDraw::WaitForVerticalBlank(unsigned long dwFlags)
{
    void *dd;
    void ***vt;
    int r;

    if (*(void **)((char *)this + 0x280) == 0)
        return;
    do {
        dd = *(void **)((char *)this + 0x280);
        vt = (void ***)*(void **)dd;
        r = ((ddvbFunc)vt[0x58 / 4])(dd, dwFlags, 0);
    } while (r == 0x8876021c);
}