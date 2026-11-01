// @Vertical@4 @ rva 0x11d80 (50 B + 14 pad) — pitch-near-limit check:
//   return |0x3ffc - v| <= 0x1554 (signed-16 wrap) || |0xc004 - v| <= 0x1554,
//   via @Abs@4 (movsx eax,cx).  C probes always emit an 81 e1 0xffff mask +
//   32-bit sub (w11c_03); only naked asm keeps FA's 66-forms with the param
//   pinned in si.  JLE rel targets 0x17/0x04 match FA.  @Abs@4 identity, no map.
extern int __fastcall Abs(int a);

int __declspec(naked) __fastcall Vertical(int v)
{
    __asm {
        push esi
        mov  si, cx
        mov  cx, 0x3ffc
        sub  cx, si
        call Abs
        cmp  eax, 0x1554
        jle  ret1
        mov  cx, 0xc004
        sub  cx, si
        call Abs
        cmp  eax, 0x1554
        jle  ret1
        xor  al, al
        pop  esi
        ret
    ret1:
        mov  al, 1
        pop  esi
        ret
    }
}