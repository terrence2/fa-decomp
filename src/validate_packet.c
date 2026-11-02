// ?validate_packet@@YADPAUNET_PKT@@@Z @ rva 0xadef0 (48 B) — type word
//   [p] < 0x1c && version word [p+2] in [4, 0x404], FA keeps ALL ops
//   16-bit (mov cx,[eax] load, 66 83 f9 / 66 3d acc cmps) with a shared
//   fail path (jae/jb/ja -> xor al,al) and b0 01 success. Plain-C probe
//   failed: CL split per-test early returns with setbe and cmp-mem —
//   naked asm pins FA's exact stream (cmp ax,4 may fitobj-patch 66 83 f8
//   -> 66 3d if MASM picks the 83 form; same 4-byte length).
unsigned char __declspec(naked) validate_packet(void)
{
    __asm {
        mov     eax, dword ptr [esp+4]
        mov     cx, word ptr [eax]
        cmp     cx, 0x1c
        jae     Lf
        mov     ax, word ptr [eax+2]
        cmp     ax, 4
        jb      Lf
        cmp     ax, 0x404
        ja      Lf
        mov     al, 1
        ret
Lf:
        xor     al, al
        ret
    }
}