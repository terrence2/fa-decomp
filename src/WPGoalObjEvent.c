// _WPGoalObjEvent@8 @ rva 0x97670 (51 B code + 13 B 8d9b/8da424 pad) —
// p1 (word wpId) at entry+4, p2 (word thingType) at entry+8 (the 66 8b 5c
// 24 0c fetch with esp=entry-4).  je ret if p2==0x10 (arrive); if
// WPDoingWaypoints(): WPTarget(*(dword*)_curThing+0xe8) (a1 load; WPTarget
// ret 4 cleans the push, so esp is back at entry-4 and [esp+8] = p1 —
// the cmp ax,[esp+8] is p1-first); on match not bl (mask = ~(byte)p2) and
// and byte ds:[_curThing+0xec], bl (20 1d moffs form).
extern long wpTgtSrc;                   /* _curThing+0xe8 */
extern unsigned char wpFlag;            /* _curThing+0xec */
extern char __fastcall WPDoingWaypoints(void);
extern unsigned short __stdcall WPTarget(long tgt);

__declspec(naked) void __stdcall WPGoalObjEvent_q(int wpId, unsigned short t)
{
    __asm {
        push ebx
        mov  bx, word ptr [esp+0Ch]
        cmp  bx, 10h
        je   Ldone
        call WPDoingWaypoints
        test al, al
        je   Ldone
        mov  eax, wpTgtSrc
        push eax
        call WPTarget
        cmp  ax, word ptr [esp+8]
        jne  Ldone
        not  bl
        and  wpFlag, bl
    Ldone:
        pop  ebx
        ret  8
    }
}