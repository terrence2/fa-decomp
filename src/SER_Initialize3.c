// ?SER_Initialize3@@YAJPAUCN_INFO@@J@Z @ rva 0x4bfa0 (11 B code + 5 B pad) —
// cdecl long(void *, long): call ?SER_InitializeLowLevel@@YAXXZ, return 2.
// Plain C (probe w16c_11 exact).  The extern is mapped to the FA.SMS
// mangled chunk name (named-chunk anchor rule).
extern void SerInitLowLevel(void);

long SER_Initialize3(void *a, long b)
{
    SerInitLowLevel();
    return 2;
}