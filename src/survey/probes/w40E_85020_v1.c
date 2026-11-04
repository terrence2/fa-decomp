/* rva 544800 (0x85020, 32 B, unnamed, 2 params, FPO esp, ret 8):
 * three interior long stores of ?noTimerSleep@@3JA (va 0x4f8318) at
 * +0x70 (0x4f8388), +0x6c (0x4f8384), +0x74 (0x4f838c) — FA order
 * 0x70, 0x6c, 0x74, each dir32 with delta. FA loads arg1 -> eax
 * (8b 44 24 04), arg2 -> ecx (8b 4c 24 08), stores a a b, 5-B tail
 * pad. */
extern long w40E_nts70;
extern long w40E_nts6c;
extern long w40E_nts74;

void __stdcall w40E_SetNoTimerSleep(long a, long b)
{
    w40E_nts70 = a;
    w40E_nts6c = a;
    w40E_nts74 = b;
}