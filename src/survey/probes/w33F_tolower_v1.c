// _tolower @ rva 0xd3db0 (110 B, no pad) -- FA/CRT asm: prolog cmp
// ds:__ctype+0x388 == 0 (CLIKE flag) THEN push esi/edi (cbProlog=9,
// cbRegs=2, fpo, cdecl, arg at [esp+0xc] after 2 pushes).  Fast path (C
// lcid, flag==0): mov eax,[esp+0xc]; 0x41<=c<=0x5a -> c+0x20.  Slow path:
// cmp ds:__nstream+4 == 0 -> je (esi=0, inc ds:__nstream+8) else push
// 0x13, esi=1, call __lock; [esp+0xc] -> call __tolower_lk; edi = result;
// if esi then push 0x13 / call __unlock and return edi; else edi; dec
// ds:__nstream+8; shared pop edi/pop esi/ret tail.  Naked-asm escape
// (prolog-with-embedded-global-cmp + lock counter dance).
extern void lock(int);
extern int tolower_lk(int);
extern void unlock(int);
extern char ctype[];
extern char nstream[];

int __declspec(naked) tolower(int c)
{
    __asm {
        cmp dword ptr [ctype+388h], 0
        push esi
        push edi
        jne Lslow
        mov eax, [esp+0Ch]
        cmp eax, 41h
        jl Lret
        cmp eax, 5Ah
        jg Lret
        add eax, 20h
        pop edi
        pop esi
        ret
    Lslow:
        cmp dword ptr [nstream+4], 0
        je Lfresh
        push 13h
        mov esi, 1
        call lock
        add esp, 4
        jmp Lcall
    Lfresh:
        xor esi, esi
        inc dword ptr [nstream+8]
    Lcall:
        mov eax, [esp+0Ch]
        push eax
        call tolower_lk
        add esp, 4
        mov edi, eax
        test esi, esi
        je Lfree
        push 13h
        call unlock
        add esp, 4
        mov eax, edi
        pop edi
        pop esi
        ret
    Lfree:
        mov eax, edi
        dec dword ptr [nstream+8]
    Lret:
        pop edi
        pop esi
        ret
    }
}