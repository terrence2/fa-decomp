// __CreateFortMission@4 @ rva 0x7ea40 (16 B) — mov eax,[esp+4] / push eax / call _FortMission@4 /
//   movsx eax,al / ret 4 — stdcall forwarder; the (char) cast on an
//   int-returning callee makes CL emit the caller-side sign extension.
extern int __stdcall FortMission(int a);

int __stdcall CreateFortMission(int a)
{
    return (char)FortMission(a);
}
