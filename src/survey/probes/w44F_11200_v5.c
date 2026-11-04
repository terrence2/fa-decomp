/* rva 0x11200 (128 B) - size-class lookup at ecx+0xd (fastcall). naked:
   CL from C arithmetizes (==2^k -> sub/cmp1/sbb/and) and inlines mov+ret
   where FA shares tail const blocks; transcription is deterministic. */
__declspec(naked) long __fastcall w44F_11200(unsigned long x)
{
    __asm {
        xor  eax, eax
        mov  ax, word ptr [ecx+0xd]
        cmp  eax, 0x80
        jg   L1
        je   Lr0
        cmp  eax, 0x40
        je   Lr4
        xor  eax, eax
        ret
L1:
        cmp  eax, 0x200
        jg   L2
        je   Lr4
        cmp  eax, 0x100
        je   Lr2
        xor  eax, eax
        ret
L2:
        cmp  eax, 0x800
        jg   L3
        je   Lr4
        cmp  eax, 0x400
        je   Lr3
        xor  eax, eax
        ret
L3:
        cmp  eax, 0x2000
        jg   L4
        je   Lr1
        cmp  eax, 0x1000
        je   Lr4
        xor  eax, eax
        ret
L4:
        cmp  eax, 0x4000
        je   Lr0
        cmp  eax, 0x8000
        je   Lr0
        xor  eax, eax
        ret
Lr4:
        mov  eax, 4
        ret
Lr0:
        xor  eax, eax
        ret
Lr2:
        mov  eax, 2
        ret
Lr3:
        mov  eax, 3
        ret
Lr1:
        mov  eax, 1
        ret
    }
}