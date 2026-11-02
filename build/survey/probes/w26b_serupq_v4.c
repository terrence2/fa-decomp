// ?SER_UpdateRemoteQueueStatus@@YAXJ@Z @ rva 0x90460 (590944) — naked
// asm: FA's 39B listing verbatim. FA's increment is the a1/40/a3
// (load/inc/store) form with the bottom test on the leftover eax; CL
// either fuses volatile ++ to ff 05 or caches the global in a register
// (v2/v3) — the entry-test a1-before-arg-load order also lands only in asm.
extern unsigned long serQtailG;              /* _serQtailG -> ?Ctrl+0x1a4 */

__declspec(naked) void __cdecl SER_UpdateRemoteQueueStatusq(long target)
{
    __asm {
        mov  eax, serQtailG
        mov  ecx, [esp+0x4]
        and  eax, 0xff
        cmp  eax, ecx
        je   Lsr26
Lsr12:
        mov  eax, serQtailG
        inc  eax
        mov  serQtailG, eax
        and  eax, 0xff
        cmp  eax, ecx
        jne  Lsr12
Lsr26:
        ret
    }
}