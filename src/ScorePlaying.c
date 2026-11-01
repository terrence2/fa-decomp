// ?ScorePlaying@@YIDXZ @ rva 0x32aa0 (16 B) — cmp [scoreStart],0 / setne al /
// ret. CL gives this only when the function RETUNS the bool as unsigned char:
// a long return folds to cmp [mem],1 / sbb/inc (w12a_04), a signed char local
// gives setne cl + movsx (w12a_17). probe w12a_16 byte-exact.
extern void *scoreStart;

unsigned char __fastcall ScorePlaying_q(void)
{
    return scoreStart != 0;
}
