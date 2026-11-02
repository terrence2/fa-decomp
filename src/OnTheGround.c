/* OnTheGround - FA rva 0x116a0 (71328) - EXACT probe verdict, tier1_a_r2.json entry 'OnTheGround_v4'
 * Form: patch-hybrid
 * Levers: 3x 1-byte modrm/opcode patches over plain C
 * Maps: _otg15=_curThing+0x15
 * patch 0x1e: modrm 87->88
 * patch 0x24: ->15
 * patch 0x2a: ->ca
 * Probes: v1-v4
 */
// _OnTheGround@0 @ rva 0x116a0 (64 B) — FA asm: 66 a1 <_curId> (word load
//   into ax, stale uppers)/53 (push ebx)/6a 01/6a 00/6a 00/68 <_curThing+
//   0x11>/68 <_curThing>/50 (push eax)/e8 _T_Info@24/8d 88 00 01 00 00
//   (lea ecx,[eax+0x100])/8b 15 <_curThing+0x15>/3b ca (cmp ecx,edx)/
//   0f 9d c3 (setge bl)/8a c3 (mov al,bl)/5b/c3.  Asks T_Info(curId,
//   curThing, curThing+0x11, 0, 0, 1) and returns whether T_Info's result
//   + 0x100 >= the dword at curThing+0x15.  Plain C: the 66 a1 + push eax
//   short-global-arg form is the FlightControlOverMe idiom (wave: WNGPart(
//   curId,0,0)); the char result stages through a register local (bl, with
//   ebx pushed prologue-style) exactly as written.  Probe
//   build/w4probe/b20a_otg_v1.obj — exact modulo fixup dwords.
extern unsigned short curId;   /* identity _curId */
extern char curThing[];        /* identity _curThing */
extern long otg15;             /* _curThing+0x15 */

extern long __stdcall T_Info(short a, char *b, char *c, long d, long e, int f);

char __stdcall OnTheGround_q(void)
{
    char r;
    r = (T_Info(curId, curThing, curThing + 0x11, 0, 0, 1) + 0x100 >= otg15);
    return r;
}
/* v4 = b20a_ontheground_v1 spelling + 3 one-byte reg-field patches
 * (0x1d lea edx->ecx, 0x23 mov ecx->edx, 0x29 cmp edx,ecx->cmp ecx,edx) */
