// _towupper @ rva 0xe4460 (117 B, fpo/esp, cbProlog=9 cbRegs=2) -- CRT
// asm sibling of _tolower (converted wave 33).  FA prolog cmp
// ds:[__ctype+0x388],0 comes BEFORE push esi/edi; word fast path
// 0x61..0x7a -> -0x20 (jb/ja, word cmp); slow path __nstream lock
// counter dance; esi-steared unlock-vs-free tails share the chunk-end
// pop edi/pop esi/ret.  Whole-body naked-asm escape (same wall as
// tolower: global-cmp-embedded prolog + counter dance reorder).
extern void lock(int);
extern int towupper_lk(int);
extern void unlock(int);
extern char ctype[];
extern char nstream[];

int __declspec(naked) towupper(int c)
{
    __asm {
        cmp dword ptr [ctype+388h], 0
        push esi
        push edi
        jne Lslow
        mov ax, word ptr [esp+0Ch]
        cmp ax, 61h
        jb Ltail
        cmp ax, 7Ah
        ja Ltail
        sub ax, 20h
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
        call towupper_lk
        mov di, ax
        add esp, 4
        test esi, esi
        je Lfree
        push 13h
        call unlock
        mov ax, di
        add esp, 4
        pop edi
        pop esi
        ret
    Lfree:
        mov ax, di
        dec dword ptr [nstream+8]
    Ltail:
        pop edi
        pop esi
        ret
    }
}