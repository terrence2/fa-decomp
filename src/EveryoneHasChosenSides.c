/* _EveryoneHasChosenSides@0 @ rva 0xa24c0 — naked asm (CL folds numComputers into mem test) */
extern int numComputers;
extern unsigned char humanChoseSide[];

void __declspec(naked) EveryoneHasChosenSides(void)
{
    __asm {
        push ebx
        xor eax, eax
        mov ecx, numComputers
        cmp ecx, eax
        jle done
        mov edx, offset humanChoseSide
    L:
        mov ebx, [edx]
        cmp ebx, -1
        je ret0
        add edx, 4
        inc eax
        cmp eax, ecx
        jl L
    done:
        mov al, 1
        pop ebx
        ret
    ret0:
        xor al, al
        pop ebx
        ret
    }
}