// __lock_file2 @ rva 0xd7240 — C v1
extern void __cdecl lockX(int);
__declspec(dllimport) void __stdcall EnterCriticalSectionX(void *);

void __cdecl lockfile2q(int fh, void *cs)
{
    if (fh < 0x15)
    {
        lockX(fh + 0x1c);
        return;
    }
    EnterCriticalSectionX((char *)cs + 0x20);
}
