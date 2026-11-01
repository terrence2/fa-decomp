// @G_NextTab@4 @ rva 0xb49d0 (64 B) — FA asm:
//   push esi / xor edx,edx / cmp word [tabStops],-1 / je retc /
//   eax=&tabStops / loop: movsx esi,[eax] / cmp esi,ecx / jg found /
//   add eax,2 / inc edx / cmp word [eax],-1 / jne loop /
//   retc: mov eax,ecx / pop / ret / found: movsx eax,word [tabStops+edx*2]
// / pop / ret
// Returns the next tab stop past `c` from the -1-terminated tabStops table
// (or c itself if none). Naked-asm escape: the -1 terminator compare is a
// movsx esi then 32-bit cmp against the param held in ecx across the loop,
// and the found-arm sib is scale-2 word indexing — the plain-C round
// pinned cursor/index/param to different regs (probe b19b_gnt_v1 FAIL),
// CL's reg plan is not steerable. Note MASM bracket subscripts are BYTE
// offsets: `tabStops[edx*2]` emits sib 0x55 (scale-2, no base) for
// 0f bf 04 55; `tabStops[edx*1]` collapsed to a scale-1 modrm and missed
// it. No maps — identity resolves (probe b19b_gnt_v2 exact).
extern short tabStops[];

long __declspec(naked) __fastcall G_NextTab(long c)
{
    __asm {
        push esi
        xor edx, edx
        cmp word ptr tabStops[0], -1
        je  Lretc
        mov eax, OFFSET tabStops
    Lloop:
        movsx esi, word ptr [eax]
        cmp esi, ecx
        jg  Lfound
        add eax, 0x2
        inc edx
        cmp word ptr [eax], -1
        jne Lloop
    Lretc:
        mov eax, ecx
        pop esi
        ret
    Lfound:
        movsx eax, word ptr tabStops[edx*2]
        pop esi
        ret
    }
}