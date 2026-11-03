/* w31F / do_shape_name @ rva 842604 (0xcdb6c) 56 B gap (no FPO)
 * FA: mov edi,0x518800(=shapeName); L: mov al,[esi]; lea esi,[esi+1];
 * mov [edi],al; lea edi,[edi+1]; or al,al; jne L;
 * mov ax,[esi]; lea esi,[esi+2]; movzx ebx,al;
 * jmp dword ptr [vector_table+ebx*2]  (sib 45 ff 24 5d <0x513c58>);
 * int3; ...same 3-instr header...; jmp dword ptr [...] ; ret; cs-nop pad */
extern char shapeName[];
extern void *vector_table[];

void __declspec(naked) do_shape_name(void)
{
    __asm {
        mov edi, OFFSET shapeName
    L1:
        mov al, [esi]
        lea esi, [esi+1]
        mov [edi], al
        lea edi, [edi+1]
        or al, al
        jne L1
        mov ax, [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp dword ptr vector_table[ebx*2]
        int 3
        mov ax, [esi]
        lea esi, [esi+2]
        movzx ebx, al
        jmp dword ptr vector_table[ebx*2]
        ret
        nop
        nop
        nop
    }
}