// @FMBayIsOpen@0 @ rva 0x51d80 (16 B) — cmp word[curThing+0x23a],0 /
//   sete al / ret (char return: CL skips the eax zeroing)
extern unsigned char curThing[];

char __fastcall FMBayIsOpen(void)
{
    return *(unsigned short *)(curThing + 0x23a) == 0;
}
