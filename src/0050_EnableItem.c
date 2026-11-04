// ?EnableItem@@YIXG@Z @ rva 0xcbf0 — clear bit 1 of the found dialog item's
//   flags word
extern int enableHelper(void);
void EnableItem_q(void)
{
    int v = enableHelper();
    if (v != 0)
        *(unsigned short *)(v + 0x10) &= 0xfffd;
}
