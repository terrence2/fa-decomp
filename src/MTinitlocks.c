/* MTinitlocks - FA rva 0xd70d0 (880848) - EXACT probe verdict, tier1_a_r1.json entry 'MTinitlocks_v2'
 * Form: plain C
 * Levers: dllimport __declspec(dllimport) decl drops CL's extra indirection frame
 * Probes: v1,v2
 */
void __declspec(dllimport) __stdcall InitializeCriticalSection(void *cs);
extern char _locktable[];

void _mtinitlocks(void)
{
    InitializeCriticalSection(*(void **)((char *)_locktable + 0x44));
    InitializeCriticalSection(*(void **)((char *)_locktable + 0x34));
    InitializeCriticalSection(*(void **)((char *)_locktable + 0x24));
    InitializeCriticalSection(*(void **)((char *)_locktable + 0x4));
}
