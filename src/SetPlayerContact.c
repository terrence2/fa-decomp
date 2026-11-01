// @SetPlayerContact@4 @ rva 0x14180 — 16-bit compare-then-store on
//   contactId (probe d96 exact; unsigned short param keeps the value in si).
extern unsigned short contactId;

void __fastcall SetPlayerContact_q(unsigned short a)
{
    if (a != contactId) contactId = a;
}
