// _CTRespondToCancelCmdBuf@0 @ rva 0x63e50 (64 B) — FA asm: a0 <_curThing>+0
//   (byte read of the pointer variable's low byte)/3c 02/74 04/3c 04/75 26/
//   a1 <_curThing+0x110>/85 c0/74 1d/a0 <_serviceTicks+0x104>/84 c0/75 14/
//   e8 $FA$_t_465ab0/b9 01 00 00 00/e8 $FA$_t_463e90 (enters with ecx=1; the
//   463e90 body starts `test cl,cl`)/e9 $FA$_t_465ae0 (tail jmp)/c3.  Naked-
//   asm escape: a0 byte moffs on a dword pointer global plus the explicit
//   mov ecx,1 fastcall arg-passing are not steerable forms; the rel call/jmp
//   targets are unnamed gap chunks ($FA$_t_), so each call extern maps TO
//   the gap anchor.  Probe build/w4probe/w19_ctrespond_v1.obj — exact.
extern char ctLoByte[];      /* _curThing +0 — byte read of the pointer var */
extern long ctCancelList[];  /* _curThing +0x110 */
extern char ctSvcFlag[];     /* _serviceTicks +0x104 */

extern void ctRspA(void);    /* $FA$_t_465ab0 (cdecl, 0 args) */
extern void ctRspB(void);    /* $FA$_t_463e90 (entering with ecx=1) */
extern void ctRspC(void);    /* $FA$_t_465ae0 (tail jmp) */

__declspec(naked) void __stdcall CTRespondToCancelCmdBuf_f(void)
{
    __asm {
        mov al, ctLoByte
        cmp al, 2
        je Ld
        cmp al, 4
        jne Rtn
    Ld:
        mov eax, dword ptr ctCancelList
        test eax, eax
        je Rtn
        mov al, ctSvcFlag
        test al, al
        jne Rtn
        call ctRspA
        mov ecx, 1
        call ctRspB
        jmp ctRspC
    Rtn:
        ret
    }
}