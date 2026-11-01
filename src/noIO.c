// ?noIO@@YAJJPAD@Z @ rva 0x92d00 (16 B, FPO fpo/esp params=2 dwords) —
// placeholder returning 0 (xor eax,eax / ret); 13-B lea tail run is
// census filler.
long noIO(int a, char *b)
{
    return 0;
}