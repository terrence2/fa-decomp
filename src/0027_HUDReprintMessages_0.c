// _HUDReprintMessages@0 @ rva 0x5dd0 (48 B) — FA asm: a1 <_hud+0xa18>/68
//   0x2d6/68 <lastWasInQuickCreator+0x4c>/a3 <_unitRight+0x10> (store
//   interleaved between the src and dst pushes)/68 <_hud+0x348>/e8 _memmove
//   (cdecl, add esp,0xc)/a1 <_timerTicks>/a3 <_unitUp+0x10>/ret.  Pulls the
//   dword at hud+0xa18 across the 0x2d6-byte message-ring memmove (src =
//   lastWasInQuickCreator+0x4c, dst = hud+0x348), then stamps timerTicks
//   into unitUp+0x10.  Plain C: CL schedules the a3 store into the memmove
//   arg-push slot itself (probe b20f_HUDReprintMessages exact; v1's named local v
//   kept the value in esi across the call — the direct global-to-global
//   statement streams eax and the store lands between push src and push
//   dst).  memmove stays a plain cdecl call (CL 4.2 does not intrinsicize
//   it; C4163 confirms).  Probe build/w4probe/b20f_HUDReprintMessages.obj.obj — exact
//   modulo fixup dwords.
extern void *__cdecl memmove(void *d, const void *s, unsigned n);

extern char hrMsgSrc[];   /* ?lastWasInQuickCreator@@3DA+0x4c */
extern char hrMsgDst[];   /* _hud+0x348 */
extern char hrTop[];      /* _hud+0xa18 */
extern long hrR0;         /* _unitRight+0x10 */
extern long hrU10;        /* _unitUp+0x10 */
extern long timerTicks;   /* _timerTicks */

void HUDReprintMessages_q(void)
{
    hrR0 = *(long *)hrTop;
    memmove(hrMsgDst, hrMsgSrc, 0x2d6);
    hrU10 = timerTicks;
}