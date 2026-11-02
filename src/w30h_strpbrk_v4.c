/* rva 907968 (0xddac0) _strpbrk 64 B
 * plain-C fill+scan loop compiles to rep stosd/shl-or (v1-v3), CL 4.2 never
 * folds 1<<(c&7) to bts nor push-fills the map -- naked inline asm transcript.
 */
__declspec(naked) char * __cdecl strpbrk(char *string, char *control)
{
    __asm {
        push ebp
        mov ebp, esp
        push esi
        xor eax, eax
        push eax
        push eax
        push eax
        push eax
        push eax
        push eax
        push eax
        push eax
        mov edx, [ebp+0ch]
        _emit 0x2e
        _emit 0x8b
        _emit 0xc0
scan_set:
        mov al, [edx]
        or al, al
        je scan_done
        inc edx
        bts dword ptr [esp], eax
        jmp scan_set
scan_done:
        mov esi, [ebp+08h]
scan_str:
        mov al, [esi]
        or al, al
        je scan_exit
        inc esi
        bt dword ptr [esp], eax
        jae scan_str
        lea eax, [esi-01h]
scan_exit:
        add esp, 020h
        pop esi
        _emit 0c9h            /* leave -- inline-asm `leave` is eaten by CL (wave-21) */
        ret
    }
}