// _GRPWingmen@8 @ rva 0x5ea40 (48 B) — FA asm: byte-for-byte the WNGWingmen
// plan against the group tables (read groupSizes[id] - 1 into *out, return
// groupIds + id*20 + 2). Naked-asm escape for the same reasons as
// WNGWingmen (probe b19b_grpwm_v1 exact; no maps — identity resolves).
extern char groupIds[];
extern unsigned char groupSizes[];

__declspec(naked) void __stdcall GRPWingmen(long id, long *out)
{
    __asm {
        mov   ecx, [esp+8]
        test  ecx, ecx
        je    skip
        xor   edx, edx
        mov   eax, [esp+4]
        mov   dl, byte ptr groupSizes[eax]
        dec   edx
        mov   [ecx], edx
        jmp   cont
skip:
        mov   eax, [esp+4]
cont:
        shl   eax, 2
        lea   eax, dword ptr groupIds[eax*4+eax+2]
        ret   8
    }
}