// _PROJEngineState@0 @ rva 0xbd510 (64 B) — FA asm (stdcall, FPO frame):
//   66 a1 <_currentT> (mov ax,[currentT])/66 2b 05 <_curThing+0xe8>
//   (sub ax,word [curThing+0xe8] — 16-bit diff; the +0xe8 dword belongs to
//   curThing, NOT curThingType+0xe8 = 0x508c08)/0f bf d0 (movsx edx,ax)/
//   33 c0 (xor eax)/66 a1 <_curThingType+0xff> (mov ax,word tpf)/
//   3b c2 (cmp eax,edx)/7e 04 (jle skip)/66 33 c0 (xor ax,ax)/c3 (ret 0)/
//   33 c9/33 c0/66 8b 0d <_curThingType+0x101> (mov cx,word tpw)/
//   3b ca (cmp ecx,edx)/0f 9e c0 (setle al)/40 (inc EAX — 32-bit inc)/c3.
//   Returns engine-state: 0 when tpf > d, else (tpw <= d)+1 where
//   d = currentT - word[curThing+0xe8].  Naked-asm escape: the ushort
//   return makes CL 4.2 truncate the +1 to inc ax (66 40) while FA has the
//   32-bit inc eax (40) — and the symmetric 66 33 c0 ret-0 path pins the
//   return type as 16-bit; 4 C probes (plain, unsigned short tf, (long)
//   cast, long r local) all land on 66 40.  The 66 a1 moffs ax caches and
//   the curThing/curThingType alias offsets come in as mapped externs.
//   Probe build/w4probe/b20b_proj_v5.obj — exact.
extern unsigned short currentT;   /* _currentT (identity) */
extern unsigned short projTf;     /* _curThing+0xe8 */
extern unsigned short projTpF;    /* _curThingType+0xff */
extern unsigned short projTpW;    /* _curThingType+0x101 */

__declspec(naked) unsigned short __stdcall PROJEngineState(void)
{
    __asm {
        mov ax, word ptr currentT
        sub ax, word ptr projTf
        movsx edx, ax
        xor eax, eax
        mov ax, word ptr projTpF
        cmp eax, edx
        jle Lcalc
        xor ax, ax
        ret
    Lcalc:
        xor ecx, ecx
        xor eax, eax
        mov cx, word ptr projTpW
        cmp ecx, edx
        setle al
        inc eax
        ret
    }
}