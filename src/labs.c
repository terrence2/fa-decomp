// _labs @ rva 0xd4b50 (10 B) — mov eax,[esp+4] / cdq / xor eax,edx /
//   sub eax,edx / ret  (the abs sign-trick). C identifier renamed to avoid
//   CL's labs intrinsic (C2169); the fitted obj carries FA's chunk name.
long __cdecl labs_(long x)
{
    return x < 0 ? -x : x;
}
