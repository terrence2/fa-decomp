// __lock_file2 @ rva 0xd7240 — C v4 (#pragma optimize("y", off): the ebp
// prolog FA's prebuilt-CRT obj has, like w24b_unlock; if-true branch
// inline = lock path, EnterCritical path falls to end — FA has 7d0d
// jge -> ECS path at 0x19; CL never folds the cdecl cleanup into
// mov esp,ebp and saves a dead ebx — handled at fitobj)
#pragma optimize("y", off)
extern void __cdecl lockX(int);
__declspec(dllimport) void __stdcall EnterCriticalX(void *pcs);

void __cdecl lockfile2q(int fh, void *cs)
{
    if (fh < 0x14)
    {
        lockX(fh + 0x1c);
        return;
    }
    EnterCriticalX((char *)cs + 0x20);
}