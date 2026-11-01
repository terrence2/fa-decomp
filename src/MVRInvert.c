// _MVRInvert @ rva 0xa9620 (32 B) — adds 0x7ff8 to three curThing word fields
// (reg-form 66 01 05 adds from one b8 imm load). A long local v is what keeps
// CL in the reg-add form (const-imm gives 66 81 05); probe w12a_02 byte-exact.
extern char curThing[];

void __fastcall MVRInvert_q(void)
{
    long v = 0x7ff8;
    *(unsigned short *)(curThing + 0x23) += v;
    *(unsigned short *)(curThing + 0x1d) += v;
    *(unsigned short *)(curThing + 0x21) += v;
}
