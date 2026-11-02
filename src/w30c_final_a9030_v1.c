/* 0xa9030 — v2: (~y) | x — FA does not eax (arg2) then or eax,ecx (arg1) */
int __cdecl w30c_negor(int x, int y)
{
    return (~y) | x;
}
