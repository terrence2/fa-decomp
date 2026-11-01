// _GRPInit@0 @ rva 0x5e7c0 (48 B) — FA asm: 57/33 c0/bf <_groupIds>/b9 32/
//   f3 ab (0x32 dwords zero to _groupIds)/a3 <_groupSizes>/a3 <+0x4>/b9
//   <_groupSizes>/5f/66 89 41 08/ret.  Naked-asm escape, same toolchain
//   diff as WNGInit (CL 66 a3 moffs + reorder vs FA's ecx/pop/word store).
//   Probe build/w4probe/b17_grpinit_n1.c — exact modulo fixup dwords.

extern char groupIds[];
extern long groupSizes[];

__declspec(naked) void GRPInit(void) {
    __asm {
        push edi
        xor eax, eax
        mov edi, offset groupIds
        mov ecx, 0x32
        rep stosd
        mov dword ptr [groupSizes], eax
        mov dword ptr [groupSizes + 4], eax
        mov ecx, offset groupSizes
        pop edi
        mov word ptr [ecx + 8], ax
        ret
    }
}