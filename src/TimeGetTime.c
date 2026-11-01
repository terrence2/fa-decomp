// _timeGetTime@0 @ rva 0xd330c (6 B) — WINMM import pass-through thunk:
//   jmp dword ptr [__imp__timeGetTime]
// 6-byte ff 25 + IAT disp32; naked asm (the 1/2-arg family thunks cannot be
// pure C — CL would re-push/copy the args — w14c_c probes 6 bytes for both
// naked and pure-C 0-arg forms; naked kept uniform across the band).
extern void *impTimeGetTime[];
unsigned long __declspec(naked) __stdcall timeGetTime(void)
{
    __asm { jmp dword ptr [impTimeGetTime] }
}
