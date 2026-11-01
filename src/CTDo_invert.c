// _CTDo_invert @ rva 0x65680 (48 B) — gate byte at _serviceTicks+0xec, then
//   the symmetric signed range check on _curThing+0x1f: invert (tail jmp e9
//   to _MVRInvert) when |heading| >= 0x3e90, else return.  The && form gives
//   FA's cmp-word-0x3e90 / jge-tail, cmp-word-0xc170 / jg-ret layout; both
//   compares re-read the memory operand (0xc170 = -0x3e90 as imm16).
extern char serviceTicks[];
extern char curThing[];
extern void MVRInvert(void);
void CTDo_invert_q(void)
{
    if (serviceTicks[0xec])
        return;
    if (*(short *)(curThing + 0x1f) < 0x3e90 &&
        *(short *)(curThing + 0x1f) > -0x3e90)
        return;
    MVRInvert();
}