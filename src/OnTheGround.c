// _OnTheGround@0 @ rva 0x116a0 (64 B) — FA asm: 66 a1 <_curId> (word load
//   into ax, stale uppers)/53 (push ebx)/6a 01/6a 00/6a 00/68 <_curThing+
//   0x11>/68 <_curThing>/50 (push eax)/e8 _T_Info@24/8d 88 00 01 00 00
//   (lea ecx,[eax+0x100])/8b 15 <_curThing+0x15>/3b ca (cmp ecx,edx)/
//   0f 9d c3 (setge bl)/8a c3 (mov al,bl)/5b/c3.  Asks T_Info(curId,
//   curThing, curThing+0x11, 0, 0, 1) and returns whether T_Info's result
//   + 0x100 >= the dword at curThing+0x15.  Naked-asm escape: plain C
//   probes (b20a_otg_v1/v2/v3) reproduce the whole body including the
//   66 a1 + push eax short-global-arg form, but CL 4.2 always assigns the
//   lea result to edx and the global load to ecx — the mirror of FA's
//   lea ecx/8b 15 edx (3 probes: plain, temp, split-stmt; same CL
//   operand-assignment tell as the two-global compare family).  Probe
//   build/w4probe/b20f_OnTheGround.obj — exact.
extern unsigned short curId;   /* identity _curId */
extern char curThing[];        /* identity _curThing */
extern long otg15;             /* _curThing+0x15 */

extern long __stdcall T_Info(short a, char *b, char *c, long d, long e, int f);

__declspec(naked) char __stdcall OnTheGround_q(void)
{
    __asm {
        mov ax, word ptr curId
        push ebx
        push 1
        push 0
        push 0
        push offset curThing + 0x11
        push offset curThing
        push eax
        call T_Info
        lea ecx, [eax+0x100]
        mov edx, dword ptr otg15
        cmp ecx, edx
        setge bl
        mov al, bl
        pop ebx
        ret
    }
}