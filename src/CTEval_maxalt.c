// _CTEval_maxalt @ rva 0x64720 (48 B) — twin of CTEval_alt: FA asm
//   56/6a 00/66 a1 <_curId>/8b 35 <curThingType+0x79> (esi load interleaved
//   after the arg-6 push)/6a 00 6a 00/68 <curThing+0x11>/68 <curThing>/50/
//   e8 _T_Info@24/2b f0/c1 fe 08/8b c6/5e/ret.  Naked-asm escape: same
//   push-interleave ordering as CTEval_alt (CL hoists the load).
//   Probe build/w4probe/b17_ctevalmax_v1.c — exact modulo fixup dwords.

extern unsigned short curId;
extern char curThing[];
extern char curThingType[];

extern long __stdcall T_Info(long a, long b, long c, long d, long e, long f);

__declspec(naked) void CTEval_maxalt(void) {
    __asm {
        push esi
        push 0
        mov ax, curId
        mov esi, dword ptr curThingType + 0x79
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