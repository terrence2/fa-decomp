// __lock_file2 @ rva 0xd7240 — C v3 (no pragma: plain /O2 gave the ebp
// prolog in the lockexit precedent; if-true branch inline = lock path,
// EnterCritical path jumps to end — FA has jge -> ECS path at 0x19)
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