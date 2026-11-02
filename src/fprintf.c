// _fprintf @ rva 0xd5ce0 (73 B, FPO fpo/esp params=2) — CRT fprintf:
// lock the stream (esi = 1st param, [esp+0xc] after the two saves), the
// odd push edi/push esi pair reserves the stbuf arg slot (popped by the
// two add esp,4), __stbuf redirects the FILE if it's stdout/stderr
// (returns the real stream in eax -> edi), builds the in-frame va_list
// (lea eax,[esp+0x18] = first variadic) and calls the dopr engine
// (3 args: eax-ptr, ecx=fmt, esi=stream), saves the char count in ebx,
// flushes (esi,edi) via the flush helper, unlocks, returns ebx. The
// push edi-before-initialization + slot accounting is FA's own CL output
// shape — naked asm.
extern void lockFileX(void);
extern void stbufX(void);
extern void doprX(void);
extern void flushX(void);
extern void unlockFileX(void);

void __declspec(naked) fprintfQ(void)
{
    __asm {
        push ebx
        push esi
        mov  esi, dword ptr [esp+0xc]
        push edi
        push esi
        call lockFileX
        add  esp, 4
        push esi
        call stbufX
        mov  ecx, dword ptr [esp+0x18]
        add  esp, 4
        mov  edi, eax
        lea  eax, dword ptr [esp+0x18]
        push eax
        push ecx
        push esi
        call doprX
        add  esp, 12
        mov  ebx, eax
        push esi
        push edi
        call flushX
        add  esp, 8
        push esi
        call unlockFileX
        add  esp, 4
        mov  eax, ebx
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}