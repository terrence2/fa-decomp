/* @Sqrt@4 @ rva 0xd2974 (124 B, fastcall arg in ecx; NO x87 - integer
 * Newton-Raphson with sqrt_table lookup) -- w45B v1. Naked-asm transcription.
 * Fast paths: bucket test a9 mask chains (0xfc000000/0x3f00000/0xfc000/
 * 0x3c00), each pair of shr's splits high nibbles then halves an index for
 * the 8b 1c 9d scaled load (sqrt_table[ebx*4]; dis.py elides these sib-9d
 * loads). Tail: integer NR step div ebx, (x/i+i)/2, or 0 for zero input.
 * Base-register-in-disp spelling: sym[index] form (MASM scale syntax) -
 * [reg*4+sym] gets base/parts dropped by CL 4.2's inline-asm folder, same
 * family as the [eax+anchor]->[anchor] fold this wave. */
extern unsigned long sqrt_table[];

void __declspec(naked) __fastcall Sqrt_45b(unsigned long x)
{
    __asm {
        push ebx
        mov  eax, ecx
        mov  ebx, eax
        test eax, 0xfc000000
        je   w45bsq_l1
        shr  ebx, 0x16
        mov  ebx, dword ptr sqrt_table[ebx*4]
        shr  ebx, 0xd
        jmp  w45bsq_end
w45bsq_l1:
        test eax, 0x3f00000
        je   w45bsq_l2
        shr  ebx, 0x10
        mov  ebx, dword ptr sqrt_table[ebx*4]
        shr  ebx, 0x10
        jmp  w45bsq_end
w45bsq_l2:
        test eax, 0xfc000
        je   w45bsq_l3
        shr  ebx, 0xa
        mov  ebx, dword ptr sqrt_table[ebx*4]
        shr  ebx, 0x13
        jmp  w45bsq_end
w45bsq_l3:
        test eax, 0x3c00
        je   w45bsq_l4
        shr  ebx, 0x4
        mov  ebx, dword ptr sqrt_table[ebx*4]
        shr  ebx, 0x16
        jmp  w45bsq_end
w45bsq_l4:
        mov  ebx, dword ptr sqrt_table[ebx*4]
        shr  ebx, 0x18
w45bsq_end:
        test ebx, ebx
        je   w45bsq_zero
        xor  edx, edx
        div  ebx
        add  eax, ebx
        shr  eax, 1
        pop  ebx
        ret
w45bsq_zero:
        xor  eax, eax
        pop  ebx
        ret
    }
}