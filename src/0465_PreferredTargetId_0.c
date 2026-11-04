// _PreferredTargetId@0 @ rva 0x636b0 (48 B) — dword at _curThing+0xf0: bit31
// set -> mov ecx,eax / e9 tail-jump into $FA$_t_45dc60 (the wing relink,
// reads the id in cx); bit30 set -> clears the LOW word (66 33 c0 xor ax,ax)
// — C has no low-word clear form, naked asm (probe w12a_14 byte-exact).
extern long prefThingPtr;
extern long __fastcall prefTailFn(long t);

__declspec(naked) long __stdcall PreferredTargetId_q(void)
{
    __asm {
        mov eax, prefThingPtr
        test eax, 80000000h
        je L1
        mov ecx, eax
        jmp prefTailFn
    L1:
        mov eax, prefThingPtr
        test eax, 40000000h
        je L2
        xor ax, ax
    L2:
        ret
    }
}
