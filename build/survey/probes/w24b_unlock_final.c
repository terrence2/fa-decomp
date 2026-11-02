// __unlock @ rva 0xd71e0 (881120) — 32 B = 0x17 code + 9 B cc pad. FA bytes:
//   55                      push ebp
//   8b 44 24 08             mov eax,[esp+8]          (arg: locknum)
//   8b ec                   mov ebp,esp
//   8b 0c 85 a8 a0 51 00    mov ecx,[__locktable+eax*4]
//   51                      push ecx
//   ff 15 1c a6 58 00       call ds:[__imp__LeaveCriticalSection]
//   5d                      pop ebp
//   c3                      ret
// i.e. LeaveCriticalSection(__locktable[locknum]). EXACT fit — byte-verify
// PASS, no --tail-accept; tail = census-proven cc*9.
//
// Recipe: CL /c /O2 /Gy /G5 + `#pragma optimize("y", off)` gives the ebp
// prolog FA's prebuilt-CRT obj has (a plain /O2 compile would go fpo/esp),
// but CL also saves/restores ebx it never uses (probe v1 emitted
// 55+8b442408+8bec+53..5b+5d). Two 1-byte deletes remove the dead saves:
//   --patch '7,1,'  -- second-patch offset is post-first-patch:
//   --patch '21,1,' (deletes the 5b; provenance: toolchain-diff — CL saves
//   callee-save ebx that FA's compiler left out under its own prolog rules)
//
// fitobj:
//   python3 tools/fitobj.py build/survey/probes/w24b_unlock_v1.obj 881120 \
//     --map '__locktableX=__locktable' \
//     --map '__lcsX=__imp__LeaveCriticalSection' \
//     --patch '7,1,' --patch '21,1,' build/survey/probes/w24b_unlock_final_fit.obj
//
// The [imm32+eax*4] table load falls out of an extern pointer-array read
// (_locktableX[n], the FA data chunk __locktable @ 0x11a0a8 holds 4-byte
// entries); the ff 15 IAT call falls out of an extern function-POINTER read
// + call — same shape __declspec(dllimport) would give, and the map points
// the obj's pointer-variable symbol straight at the IAT slot.
extern void (_stdcall *_lcsX)(void *a);   /* __lcsX -> __imp__LeaveCriticalSection */
extern void *_locktableX[];               /* __locktableX -> __locktable */

void _unlock_q(int n)
{
    _lcsX(_locktableX[n]);
}
