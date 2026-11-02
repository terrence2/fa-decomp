// __unlock_file2 @ rva 0xd72b0 — C v1
extern void __cdecl unlockX(int);
__declspec(dllimport) void __stdcall LeaveCriticalSectionX(void *);

void __cdecl unlockfile2q(int fh, void *cs)
{
    if (fh < 0x15)
    {
        unlockX(fh + 0x1c);
        return;
    }
    LeaveCriticalSectionX((char *)cs + 0x20);
}
