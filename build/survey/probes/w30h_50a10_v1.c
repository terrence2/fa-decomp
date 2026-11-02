/* rva 330256 (0x50a10) 32 B FPO/esp gap chunk
 * cl==0x20 / 9 / 0xd / 0xa -> al=1 else al=0; shared true-ret layout */
char __fastcall w30h_isSpaceChar(char c)
{
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}