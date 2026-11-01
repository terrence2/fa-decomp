// do_setcolor2 @ rva 0xcf370 (22 B, gap chunk — hot-path fragment lifted
// out of the do_setcolor family; runs on the caller's esi cursor). mov
// ax,[esi] + lea esi,[esi+2] advance blocks with 0f b6 movzx byte variant,
// ending in TWO eb rel8 short jmps into the SIBLING chunk
// do_setcolor_continue (+0xa and +0x0). MASMs jmp extern would be e9; the
// NLG_Return2/Notify1 escape bakes the short jmps with _emit (chunk VAs
// are link-fixed), rel8 +0x18/+0x07 raw from FA. 90 between the blocks is
// the 16B-boundary filler, emitted by hand (mid-code pad).
void __declspec(naked) do_setcolor2(void)
{
    __asm {
        mov      ax, word ptr [esi]
        lea      esi, [esi+2]
        _emit 0xeb        ; jmp short do_setcolor_continue+0xa (0x4cf390)
        _emit 0x18        ; rel8 = +0x18
        movzx    ax, byte ptr [esi-1]
        _emit 0xeb        ; jmp short do_setcolor_continue (0x4cf386)
        _emit 0x07        ; rel8 = +0x07
        _emit 0x90        ; boundary filler between the lifted hot blocks
        mov      ax, word ptr [esi]
        lea      esi, [esi+2]
    }
}