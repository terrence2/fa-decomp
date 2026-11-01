// _WNGInit@0 @ rva 0x5da90 (48 B) — FA asm: 57/33 c0/bf <_wingIds>/b9 32/
//   f3 ab (0x32 dwords zero to _wingIds)/a3 <_wingSizes>/a3 <+0x4>/b9
//   <_wingSizes>/5f/66 89 41 08/ret.  Naked-asm escape: CL always emits the
//   final word store as a 66 a3 moffs ordered before the pop edi (its own
//   spilling); FA's mov ecx,offset / pop edi / mov [ecx+8].ax order is
//   unreachable from source.  Naked-asm [sym],eax keeps the a3 forms.
//   Probe build/w4probe/b17_wnginit_n1.c — exact modulo fixup dwords.

extern char wingIds[];
extern long wingSizes[];

__declspec(naked) void WNGInit(void) {
    __asm {
        push edi
        xor eax, eax
        mov edi, offset wingIds
        mov ecx, 0x32
        rep stosd
        mov dword ptr [wingSizes], eax
        mov dword ptr [wingSizes + 4], eax
        mov ecx, offset wingSizes
        pop edi
        mov word ptr [ecx + 8], ax
        ret
    }
}