/* ?MPRequestControl@@YIXG@Z @ rva 0x71260 (96 B) -- naked-asm v3: v1's
 * only diffs were FA's redundant disp8 forms (c6 44 24 00 vs CL/MASM's
 * optimal c6 04 24; 8d 44 24 00 vs 8d 04 24) -> _emit the FA byte streams
 * verbatim; everything else matched v1 (incl. moffs with +disp). */
extern long numComputers, thisComputer;
extern void __fastcall MAPMaybeSetControl(unsigned long, unsigned short);
extern unsigned short __fastcall OBJAlias(unsigned short, unsigned long);
extern void __stdcall w35h_p46(unsigned long, void *, unsigned long,
                               unsigned long);
extern void __fastcall w35h_mpflush(unsigned char);

void __declspec(naked) __fastcall MPRequestControl(unsigned long p)
{
    __asm {
        sub esp, 4
        mov eax, DWORD PTR [numComputers]
        cmp eax, 1
        je L4
        mov eax, DWORD PTR [thisComputer]
        test eax, eax
        jne L1
        mov edx, ecx
        xor ecx, ecx
        call MAPMaybeSetControl
        add esp, 4
        ret
    L1:
        _emit 0C6h
        _emit 044h
        _emit 024h
        _emit 000h
        _emit 045h              /* mov BYTE PTR [esp+0], 45h */
        test cx, cx
        je L2
        mov edx, 1
        call OBJAlias
        mov WORD PTR [esp+1], ax
        jmp L3
    L2:
        mov WORD PTR [esp+1], 0
    L3:
        _emit 08Dh
        _emit 044h
        _emit 024h
        _emit 000h              /* lea eax, [esp+0] */
        push 1
        push 3
        push eax
        push 0
        call w35h_p46
        xor ecx, ecx
        call w35h_mpflush
    L4:
        add esp, 4
        ret
    }
}