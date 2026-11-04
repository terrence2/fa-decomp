// @MMHandleLen@4 @ rva 0x35d20 — test ecx,ecx / jz shared-tail / mov eax,
//   [ecx+8] / test eax,eax / jz shared-tail / mov eax,[ecx+0xc] / ret /
//   xor eax,eax / ret (probe w5_mmlen exact; single-exit nested if).
int __fastcall MMHandleLen(void *h)
{
    if (h) {
        int v = *(int *)((char *)h + 8);
        if (v)
            return *(int *)((char *)h + 0xc);
    }
    return 0;
}
