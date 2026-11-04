// @GetFlightEnvelope@4 @ rva 0x9b220 (48 B) — fastcall ecx = speed; the
//   ||-form with lo hoisted to a signed short local gives FA's shared
//   return-0 tail: movsx edx,+0xc2 / cmp ecx,edx / jl far / movsx eax,+0xc4
//   / cmp eax,ecx / jl far / (success) mov eax,ecx / sub edx / shl 7 / add
//   +0xbe table.  Per-guard if-returns emit two local 33 c0 c3 exits
//   instead (d14b w14b_).
extern char curThingType[];
int __fastcall GetFlightEnvelope_q(int v)
{
    short lo = *(short *)(curThingType + 0xc2);
    if (v < lo || v > *(short *)(curThingType + 0xc4))
        return 0;
    return ((v - lo) << 7) + *(long *)(curThingType + 0xbe);
}