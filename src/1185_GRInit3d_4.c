// w26a_grinit3d @ rva 0xd1f58 (858968) _GRInit3d@4 (36 B, no FPO).
// Hand-written-asm-style frame function (ebp frame; CL /O2 with fpo/esp
// would fold the prolog — that is the escape reason). FA bytes (raw):
//   55                   push ebp
//   8b ec                mov ebp,esp
//   53 56 57             push ebx / push esi / push edi
//   55                   push ebp            (extra for 8-alignment)
//   66 8b 45 08          mov ax,[ebp+8]      (param)
//   66 a3 e8 17 51 00    mov moffs16 ds:0x5117e8, ax   (_bitmap_table+0x28)
//   c7 05 28 62 58 00 00 b2 4b 00   mov dword ptr ds:0x586228, 0x4bb200
//                        (_overflow_ptr = &_unknown_divide_error)
//   5d 5f 5e 5b 5d       pop ebp / pop edi / pop esi / pop ebx / pop ebp
//   c2 04 00             ret 4
//   90                   (1 B pad)
extern char bitmap_table_t[];    /* _bitmap_table (+0x28 addend baked) */
extern char overflow_ptr_t[];    /* _overflow_ptr */
extern void unknown_divide_error(void);
__declspec(naked) void __stdcall w26a_grinit3d(void)
{
    __asm {
        push ebp
        mov ebp, esp
        push ebx
        push esi
        push edi
        push ebp
        mov ax, word ptr [ebp+8]
        mov word ptr [bitmap_table_t + 0x28], ax
        mov dword ptr [overflow_ptr_t], OFFSET unknown_divide_error
        pop ebp
        pop edi
        pop esi
        pop ebx
        pop ebp
        ret 4
    }
}