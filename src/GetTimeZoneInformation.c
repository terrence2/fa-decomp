// _GetTimeZoneInformation@4 @ rva 0xe4ee0 (6 B) - KERNEL32 import pass-through thunk.
extern void *impGetTimeZoneInformation[];
void __declspec(naked) __stdcall GetTimeZoneInformation(void)
{
    __asm { jmp dword ptr [impGetTimeZoneInformation] }
}
