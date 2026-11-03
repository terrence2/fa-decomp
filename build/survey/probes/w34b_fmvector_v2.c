/* rva 0x51420 (@FMVector@8), 80 B - v2: inline asm body (the FA shape is
   pure memory-op MASM-style codegen: add/mov moffs, mem-first cmp). */
extern short w34b_th;
extern short w34b_thi;
extern short w34b_tlo;

short __fastcall w34b_fmvector2(unsigned short a, unsigned char f)
{
    __asm {
        test dl, dl
        je  L1
        add WORD PTR w34b_th, cx
        jmp L2
L1:     mov WORD PTR w34b_th, cx
L2:     mov ax, WORD PTR w34b_th
        cmp WORD PTR w34b_thi, ax
        jle L3
        mov ax, WORD PTR w34b_thi
        mov WORD PTR w34b_th, ax
        ret
L3:     mov ax, WORD PTR w34b_th
        cmp WORD PTR w34b_tlo, ax
        jge L4
        mov ax, WORD PTR w34b_tlo
        mov WORD PTR w34b_th, ax
L4:     ret
    }
    return 0;
}