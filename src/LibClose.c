// _LibClose @ rva 0x78bf0 — mark lib slot ndx-1 in use (record stride 0xc via
//   lea edx,[ecx+ecx*2] + sib scale-4 store, d161)
extern char libAccess[];
char LibClose_q(unsigned short a)
{
    int idx = (short)(a - 1);
    *(long *)(libAccess + idx * 12) = 1;
    return 0;
}
