/* w34E_87290 @ rva 0x87290 (48 B) — stdcall word clamp: (short)[+0xc]
 * clamped to [0, (short)[+0xe].  FA reads p before the esi-less fpo
 * prolog; compares [mem],cx directly (66 39 48 0c). */
void __stdcall w34E_87290(void *p)
{
    volatile char *b = (char *)p;
    if (*(short *)(b + 0xc) < 0)
        *(short *)(b + 0xc) = 0;
    if (*(short *)(b + 0xc) > *(short *)(b + 0xe))
        *(short *)(b + 0xc) = *(short *)(b + 0xe);
}