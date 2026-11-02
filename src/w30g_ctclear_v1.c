// unnamed chunk @ rva 0x8b570 (16 B) — void cdecl, zeroes two byte fields
// of ?COMMENT_TYPE@@3W4__unnamed@@A: +0x20 and +0x80. FA: xor eax,eax /
// mov ds:[X+0x20],al / mov ds:[X+0x80],al / ret — a register-held zero char
// stored twice, so the source stages the 0 in a char local first.
extern char w30gCT1;    // COMMENT_TYPE+0x20
extern char w30gCT2;    // COMMENT_TYPE+0x80

void __cdecl w30g_ctclear(void)
{
    char c;
    c = 0;
    w30gCT1 = c;
    w30gCT2 = c;
}