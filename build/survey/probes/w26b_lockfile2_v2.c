// __lock_file2 @ rva 0xd7240 — C v2 (ebp frame forced; B2 early-return shape)
#pragma optimize("y", off)
extern void __cdecl lockX(int);
__declspec(dllimport) void __stdcall EnterCriticalX(void *pcs);

void __cdecl lockfile2q(int fh, void *cs)
{
    if (fh >= 0x14)
    {
        EnterCriticalX((char *)cs + 0x20);
        return;
    }
    lockX(fh + 0x1c);
}
