/* ?Unlock@CDirDraw@@QAEHPAVCDirDrawSurface@@@Z @ rva 0x1dd60 — tail call */
extern int __fastcall dsSurfUnlockQ(void *surf);

int __stdcall dsUnlock(void *surf)
{
    return dsSurfUnlockQ(surf);
}