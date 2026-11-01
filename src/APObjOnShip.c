/* @APObjOnShip@4 @ rva 0xbb1d0 — naked asm (dead xor edx; cmp imm32 needs OFFSET form) */
/* apShipBaseQ is _airports+0x3020 */
extern char apShipBaseQ[];
extern void *overflow_ptr[];

void __declspec(naked) __fastcall APObjOnShip(void)
{
    __asm {
        push ebx
        mov eax, offset apShipBaseQ
        xor edx, edx
    L:
        cmp word ptr [eax], cx
        jne next
        mov ebx, [eax+2]
        test ebx, ebx
        jne found
    next:
        add eax, 018h
        cmp eax, offset overflow_ptr
        jb L
        xor ax, ax
        pop ebx
        ret
    found:
        mov eax, [eax+2]
        pop ebx
        mov ax, word ptr [eax+0e6h]
        ret
    }
}