// @TurnTowardAngle@12 @ rva 0x116e0 (80 B) — FA asm (plain-C reachable):
//   negate limit if negative / diff = src - dst (short) /
//   if |diff| <= limit return src / else step dst by +limit/-limit toward
//   src. CL reg plan after inverting the outer condition
// (`if (Abs(diff) <= limit) return src;` puts the return-src inline after
// the jg — FA's jg 0a order; the exceeds-block then falls out inline).
// Uses the @Abs@4 helper (chunk identity, no map). Probe b19b_tta_v2
// (v1 had FA's jle/jg layout inverted).
extern int __fastcall Abs(short v);

short __fastcall TurnTowardAngle(short dst, short src, int limit)
{
    short diff;

    if (limit < 0)
        limit = -limit;
    diff = src - dst;
    if (Abs(diff) <= limit)
        return src;
    if (diff >= 0)
        return limit + dst;
    return dst - limit;
}