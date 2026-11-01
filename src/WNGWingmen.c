// _WNGWingmen@8 @ rva 0x5dd10 (48 B) — FA asm:
//   mov ecx,[esp+8] / test / je skip / xor edx,edx / mov eax,[esp+4] /
//   mov dl,[wingSizes+eax] / dec edx / mov [ecx],edx / jmp cont /
//   skip: mov eax,[esp+4] / cont: shl eax,2 / lea eax,[wingIds+eax*5+2] /
//   ret 8
// Reads the wing's max-wings byte (minus 1) into *out and returns the
// address of the wing-id slot: wingIds + id*20 + 2. Naked-asm escape (same
// family as WNGInit/GRPInit toolchain-diff): the `[reg+sym]` byte load and
// the sib lea with baked +2 addend, plus the shared skip/cont tail CL
// reachable in exactly this order from no C plan (probe b19b_wngwm_v1
// exact; no maps — wingSizes/wingIds resolve identity, +2 baked in lea).
extern char wingIds[];
extern unsigned char wingSizes[];

__declspec(naked) void __stdcall WNGWingmen(long id, long *out)
{
    __asm {
        mov   ecx, [esp+8]
        test  ecx, ecx
        je    skip
        xor   edx, edx
        mov   eax, [esp+4]
        mov   dl, byte ptr wingSizes[eax]
        dec   edx
        mov   [ecx], edx
        jmp   cont
skip:
        mov   eax, [esp+4]
cont:
        shl   eax, 2
        lea   eax, dword ptr wingIds[eax*4+eax+2]
        ret   8
    }
}