// __CreateFortMission2@4 @ rva 0x7ea50 (16 B) — mov eax,[esp+4] / push eax / call _FortMission2@4 /
//   movsx eax,al / ret 4 — stdcall forwarder; the (char) cast on an
//   int-returning callee makes CL emit the caller-side sign extension.
extern int __stdcall FortMission2(int a);

int __stdcall CreateFortMission2(int a)
{
    return (char)FortMission2(a);
}
