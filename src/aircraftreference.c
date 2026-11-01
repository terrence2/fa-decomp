// _AircraftReference (FA sym __AircraftReference@0) @ rva 0x7ead0 (16 B)
//   C source identifier carries a leading underscore, so the decorated
//   stdcall symbol gains the doubled prefix.
extern int __cdecl INFO2Screen(void);

int __stdcall _AircraftReference(void)
{
    return (signed char)INFO2Screen();
}
