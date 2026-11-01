// @APFind@4 @ rva 0xb9670 (64 B) — FA asm:
//   mov ax,[numAirports] / push esi / push edi / xor edi,edi /
//   cmp ax,di / jle fail / mov edx,OFFSET airports+0xe6 /
//   loop: cmp word [edx],cx / je found / add edx,0x134 / inc edi /
//   movsx esi,ax / cmp esi,edi / jg loop /
//   fail: xor eax,eax / pop edi / pop esi / ret /
//   found: lea chain edi*9/eax*2/edi+ecx*4 / pop edi / pop esi / nop /
//   lea eax,[airports+edx*4] / ret
// Linear search for airport id `c` over 0x134-byte records; returns the
// record address or 0. Naked-asm escape: FA caches numAirports in the
// 16-bit ax (66 a1 moffs) and compares it against edi in halves while the
// record-pointer loop cmps cx — a register plan CL's plain C pins
// differently (probe b19b_apf_v1 FAIL). The found-arm triple-lea chain
// (edi*9, +2, *4) with a nop pad is the exact address decode. No maps —
// identity resolves, +0xe6 addend baked by MASM (probe b19b_apf_v2 exact).
extern short numAirports;
extern char airports[];

long __declspec(naked) __fastcall APFind(short c)
{
    __asm {
        mov ax, word ptr numAirports
        push esi
        push edi
        xor edi, edi
        cmp ax, di
        jle Lfail
        mov edx, OFFSET airports + 0xe6
    Lloop:
        cmp word ptr [edx], cx
        je Lfound
        add edx, 0x134
        inc edi
        movsx esi, ax
        cmp esi, edi
        jg Lloop
    Lfail:
        xor eax, eax
        pop edi
        pop esi
        ret
    Lfound:
        lea eax, dword ptr [edi+edi*8]
        lea ecx, dword ptr [edi+eax*2]
        lea edx, dword ptr [edi+ecx*4]
        pop edi
        pop esi
        nop
        lea eax, dword ptr airports[edx*4]
        ret
    }
}