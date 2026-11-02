/* w29g ?MMUnmapFile@@YIXPAX00@Z @ 0x359c0 — v1 */
__declspec(dllimport) int __stdcall UnmapViewOfFile(void *);
__declspec(dllimport) int __stdcall CloseHandle(void *);

void __fastcall w29g_umf(void *pvFile, void *hMap, void *hFile)
{
    if (pvFile)
        UnmapViewOfFile(pvFile);
    if (hMap)
        CloseHandle(hMap);
    if (hFile)
        CloseHandle(hFile);
}