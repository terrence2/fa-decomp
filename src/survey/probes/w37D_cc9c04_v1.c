/* wave37D SetShading 0xc9c04 (92 B) v1 - full-body inline asm (reg-arg helper) */
extern short w37d_ls0, w37d_ls1, w37d_ls2;  /* _objLightSource+0/+2/+4 */
void w37d_setsh(void);                      /* SetShadingTable */
void SetShading(void)
{
    __asm {
        push edx
        push ebp
        push edi
        push esi
        movsx ebp, WORD PTR w37d_ls0
        imul ebp
        shrd eax, edx, 0Fh
        mov edi, eax
        mov eax, ebx
        movsx ebp, WORD PTR w37d_ls1
        imul ebp
        shrd eax, edx, 0Fh
        add edi, eax
        mov eax, ecx
        movsx ebp, WORD PTR w37d_ls2
        imul ebp
        shrd eax, edx, 0Fh
        add edi, eax
        sar edi, 07h
        mov ax, di
        cmp ax, 0FF01h
        jge L1
        mov ax, 0FF01h
        jmp L2
L1:     cmp ax, 00FFh
        jle L2
        mov ax, 00FFh
L2:     call w37d_setsh
        pop esi
        pop edi
        pop ebp
        pop edx
    }
}
