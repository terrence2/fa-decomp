// ?jdiv_round_up@@YAJJJ@Z @ rva 0x74f30 (16 B, FPO fpo/esp params=2
// dwords) — ceil division: (a + b - 1) / b as signed long. FA fuses
// a+b-1 into lea eax,[eax+ecx*1-1] then cdq/idiv.
long jdiv_round_up(long a, long b)
{
    return (a + b - 1) / b;
}