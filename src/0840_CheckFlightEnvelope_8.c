/* w46B_flenv_v1 - _CheckFlightEnvelope@8, FA rva 0x9b250 (635472), 160 B, tail 0500000000 (5 B)
 * stdcall ret 8, FPO esp, locals 3 dwords a@S+0/b@S+4/c@S+8, regs ebx,esi,edi.
 * FA anatomy:
 *   mov ecx,[esp+4]; sub esp,0xc; push ebx/esi/edi; call @GetFlightEnvelope@4 (fastcall, ecx=arg1)
 *   esi=eax; test; jz -> ret 1
 *   ebx = dword ptr [_curThing+0x34] >> 8   (moffs a1-form 8b 1d)
 *   edi = dword ptr [_curThing+0x15] >> 8   (8b 3d)
 *   lea eax,[esp+0x10] (&b); push; lea ecx,[esp+0x18] (&c); lea edx,[esp+0x10] (&a); push ecx; push edx;
 *   push esi; call _EnvelopeSpeedLimits@16  -> callee cleans 0x10; esp back to post-push frame
 *   eax=[esp+0x20] (arg2 stall ptr); test; if nonzero:
 *     movsx ecx,word [esi+6]; lea edx,[ecx+ecx*2]; cmp [esi+edx*2+0xa],edi; setl dl; mov [eax],dl
 *     (= *stall = ((long)tbl[3*tbl[3]+5] < mid_); tbl is short array at env+0)
 *   a=[esp+0xc] vs ebx: jle skip -> if (a > max_) return 1
 *   b=[esp+0x10] vs ebx: jg  skip -> if (b > max_) return 3
 *   c=[esp+0x14] vs ebx: setg al; dec al; and al,2 -> return c > max_ ? 0 : 2
 * abs sites: 0x22 (_curThing+0x34), 0x28 (_curThing+0x15) — interior payloads 0x34/0x15
 * rel sites: 0xa (@GetFlightEnvelope@4, identity map), 0x42 (_EnvelopeSpeedLimits@16)
 */
extern unsigned char curT[];                                   /* _curThing */
extern long *__fastcall GetFlightEnvelope(long *thing);       /* @GetFlightEnvelope@4 */
extern void __stdcall EnvelopeSpeedLimits(long *env, long *a, long *c, long *b); /* _EnvelopeSpeedLimits@16 */

char __stdcall CheckFlightEnvelope(long *thing, char *stall)
{
    long a, b, c, max_, mid_;
    long *env;
    env = GetFlightEnvelope(thing);
    if (env == 0)
        return 1;
    max_ = *(long *)(curT + 0x34) >> 8;
    mid_ = *(long *)(curT + 0x15) >> 8;
    EnvelopeSpeedLimits(env, &a, &c, &b);
    if (stall != 0)
        *(char *)stall =
            (*(long *)((short *)env + 3 * (long)*((short *)env + 3) + 5) < mid_);
    if (a > max_)
        return 1;
    if (b > max_)
        return 3;
    return c > max_ ? 0 : 2;
}