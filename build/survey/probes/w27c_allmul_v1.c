// __allmul @ rva 0xd4d40 (871744, 64 B) — CRT 64x64 multiply helper.
//   Expectation: CL re-emits a self-call for __int64*__int64 (recursion) —
//   probe to confirm the KEEP-ASM call before writing it off.
__int64 __stdcall w27c_allmul(__int64 a, __int64 b)
{
    return a * b;
}
