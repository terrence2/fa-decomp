extern long numComputers;      /* _numComputers 0x4e7604, identity */
extern long humanChoseSide[];  /* _humanChoseSide 0x51c2d8, identity */

void __declspec(naked) w35a32110(void)
{
    __asm {
        push ebx
        xor ecx, ecx
        mov eax, numComputers
        cmp eax, ecx
        jle L1
        mov edx, offset humanChoseSide
    L0:
        mov ebx, [edx]
        test ebx, ebx
        jne L2
        add edx, 4
        inc ecx
        cmp eax, ecx
        jg L0
    L1:
        mov al, 1
        pop ebx
        ret
    L2:
        xor al, al
        pop ebx
        ret
    }
}
