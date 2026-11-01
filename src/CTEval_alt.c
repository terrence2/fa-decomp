// _CTEval_alt @ rva 0x646d0 (48 B) — FA asm: 56/6a 00/66 a1 <_curId>/8b 35
//   <curThing+0x15> (esi dword load interleaved between the arg-6 push and
//   the remaining pushes)/6a 00 6a 00/68 <curThing+0x11>/68 <curThing>/50/
//   e8 _T_Info@24/2b f0/c1 fe 08/8b c6/5e/ret — (esi − T_Info(...) >> 8).  Naked-asm escape: FA interleaves the dword load after
//   the first push; CL always hoists it before the push block.
//   Probe build/w4probe/b17_ctevalalt_v1.c — exact modulo fixup dwords.

extern unsigned short curId;
extern char curThing[];

extern long __stdcall T_Info(long a, long b, long c, long d, long e, long f);

__declspec(naked) void CTEval_alt(void) {
    __asm {
        push esi
        push 0
        mov ax, curId
        mov esi, dword ptr curThing + 0x15
        push 0
        push 0
        push offset curThing + 0x11
        push offset curThing
        push eax
        call T_Info
        sub esi, eax
        sar esi, 8
        mov eax, esi
        pop esi
        ret
    }
}