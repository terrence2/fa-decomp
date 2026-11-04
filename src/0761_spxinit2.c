// ?spxinit2@@YADPAUNET_PROTOCOL@@PAUCN_INFO@@@Z @ rva 0x95130 (16 B, FPO
// fpo/esp params=2 dwords) — sets protocol->byte@0xb = 1 and returns char
// 1 (b0 01, no zero-extension in FA). The 5-B "add eax,0" tail is census
// filler (padcensus 05pad), added by fitobj.
char spxinit2(void *proto, void *cninfo)
{
    *(char *)((char *)proto + 0xb) = 1;
    return 1;
}