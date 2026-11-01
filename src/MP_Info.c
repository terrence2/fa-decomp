// ?MP_Info@@YAPAUMP_INFO@@XZ @ rva 0x92e00 (16 B) — returns the
//   ?mpInfo@@3UMP_INFO@@C instance address (b8 imm32 via the DIR32 on the
//   offset); tail pad 8d 49 00 + 8d a4 24 00 00 00 00 census filler.
extern char mpInfoArr[];
void *MP_Info_q(void)
{
    return mpInfoArr;
}