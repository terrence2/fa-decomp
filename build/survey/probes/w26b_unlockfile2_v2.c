// __unlock_file2 @ rva 0xd72b0 — C v2 (ebp frame forced; B2 early-return shape)
#pragma optimize("y", off)
extern void __cdecl unlockX(int);
__declspec(dllimport) void __stdcall LeaveCriticalX(void *pcs);

void __cdecl unlockfile2q(int fh, void *cs)
{
    if (fh >= 0x14)
    {
        LeaveCriticalX((char *)cs + 0x20);
        return;
    }
    unlockX(fh + 0x1c);
}
