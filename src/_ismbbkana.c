// __ismbbkana @ rva 0xdb7e0 (42 B) — katakana MBCS test: return 0 unless
// the code-page dword at _mbctype+0x104 is 932 (0x3a4), then
// _ismbbType(c,0,3) ($FA$_t_4db810, same 18 B bit-query family as
// ismbbtrail/ISMBBLead). FA compares the page dword in memory
// (cmp [mem],imm32); CL loads into eax first (w11a_09_ika1) — naked asm
// escape (w11a_10_ika2, byte-exact; shared xor-eax/ret exit for both je's).
extern unsigned char _mbctype[];
extern int ismbbType(int c, int mask, int flg);

int __declspec(naked) __cdecl _ismbbkana_q(unsigned int c)
{
    __asm
    {
        cmp dword ptr [_mbctype + 0x104], 0x3a4
        jne Ret0
        mov eax, [esp + 4]
        push 3
        push 0
        push eax
        call ismbbType
        add esp, 0xc
        test eax, eax
        je Ret0
        mov eax, 1
        ret
    Ret0:
        xor eax, eax
        ret
    }
}