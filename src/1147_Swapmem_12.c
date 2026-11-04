/* w36B v1: _Swapmem@12 rva 0xc2868 (108 B, gap chunk — no .debug$F).
 * Whole-body naked-asm: FA's swap is byte-tail + 16-B-block + dword-block
 * with jecxz/loop control no CL 4.2 C route produces.  Defines the public
 * _Swapmem@12 (other entries call it — layout name is the public).  No
 * externs, no relocs: exact FA linear order incl. the odd-byte preamble
 * before shr ecx,1... note FA does shr BEFORE the byte swap carry test
 * (jae), and ebp caches the words-remaining count for the word tail loop.
 */
void __declspec(naked) __stdcall Swapmem(void *s1, void *s2, unsigned long n)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        mov ecx, [ebp+10h]
        jecxz Ldone
        mov esi, [ebp+8]
        mov edi, [ebp+0Ch]
        shr ecx, 1
        jae L2
        mov al, [edi]
        xchg [esi], al
        mov [edi], al
        inc esi
        inc edi
L2:     mov ebp, ecx
        shr ecx, 3
        je L3
Ldw:    mov eax, [edi]
        xchg [esi], eax
        mov [edi], eax
        mov eax, [edi+4]
        xchg [esi+4], eax
        mov [edi+4], eax
        mov eax, [edi+8]
        xchg [esi+8], eax
        mov [edi+8], eax
        mov eax, [edi+0Ch]
        xchg [esi+0Ch], eax
        mov [edi+0Ch], eax
        add esi, 10h
        add edi, 10h
        loop Ldw
L3:     mov ecx, ebp
        and ecx, 7
        je Ldone
Lw:     mov ax, [edi]
        xchg [esi], ax
        mov [edi], ax
        add esi, 2
        add edi, 2
        loop Lw
Ldone:  pop edi
        pop esi
        pop ebx
        pop ebp
        ret 0Ch
    }
}