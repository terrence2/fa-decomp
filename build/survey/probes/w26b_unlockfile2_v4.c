// __unlock_file2 @ rva 0xd72b0 — C v4 (same recipe as lockfile2 v4)
#pragma optimize("y", off)
extern void __cdecl unlockX(int);
__declspec(dllimport) void __stdcall LeaveCriticalX(void *pcs);

void __cdecl unlockfile2q(int fh, void *cs)
{
    if (fh < 0x14)
    {
        unlockX(fh + 0x1c);
        return;
    }
    LeaveCriticalX((char *)cs + 0x20);
}