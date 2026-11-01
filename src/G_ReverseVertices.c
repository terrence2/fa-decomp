// @G_ReverseVertices@8 @ rva 0x96560 (80 B) — FA asm: push ebx / lea
// eax,[ecx+ecx*2] / push esi / push ebp / lea esi,[edx+eax*4-0xc] / cmp
// esi,edx / jbe exit / loop: dword swaps [edx]/[esi] with add edx,0xc /
// sub esi,0xc INTERLEAVED between the two stores, then word swaps at
// [edx-8]/[esi+0x10] (u), [edx-4]/[esi+0x14] (v pairs via 16-bit mov bp/cx),
// [edx-2]/[esi+0x16], ja loop / exit: pop ebp / pop esi / pop ebx / ret.
// asm escape (probe b17c_grevvtx_v2 byte-exact): C emitted a mirrored reg
// plan (v1 FAIL) — the add/sub advance between the paired dword stores and
// the ebp-relative 16-bit swap order are not schedulable from plain C; ebp
// is pushed but unused (FA's frame plan). V12 struct is exactly 12 bytes
// {long x; long y; short u; short v;} — no pad fields.
__declspec(naked) void __fastcall G_ReverseVertices(void)
{
    __asm {
        push ebx
        lea eax, [ecx+ecx*2]
        push esi
        push ebp
        lea esi, [edx+eax*4-0xc]
        cmp esi, edx
        jbe Lexit
Lloop:
        mov eax, dword ptr [edx]
        mov ecx, dword ptr [esi]
        mov dword ptr [edx], ecx
        add edx, 0xc
        mov dword ptr [esi], eax
        sub esi, 0xc
        mov ebx, dword ptr [edx-8]
        cmp esi, edx
        mov eax, dword ptr [esi+0x10]
        mov dword ptr [edx-8], eax
        mov dword ptr [esi+0x10], ebx
        mov bp, word ptr [edx-4]
        mov cx, word ptr [esi+0x14]
        mov word ptr [edx-4], cx
        mov word ptr [esi+0x14], bp
        mov ax, word ptr [edx-2]
        mov bx, word ptr [esi+0x16]
        mov word ptr [edx-2], bx
        mov word ptr [esi+0x16], ax
        ja Lloop
Lexit:
        pop ebp
        pop esi
        pop ebx
        ret
    }
}