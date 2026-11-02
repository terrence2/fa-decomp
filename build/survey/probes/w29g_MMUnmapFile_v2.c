/* w29g ?MMUnmapFile@@YIXPAX00@Z @ 0x359c0 — v2: FA param order (ecx=hFile,
 * edx=hMap, stack=pvFile; call order pvFile, hMap, hFile) */
__declspec(dllimport) int __stdcall UnmapViewOfFile(void *);
__declspec(dllimport) int __stdcall CloseHandle(void *);

void __fastcall w29g_umf(void *hFile, void *hMap, void *pvFile)
{
    if (pvFile)
        UnmapViewOfFile(pvFile);
    if (hMap)
        CloseHandle(hMap);
    if (hFile)
        CloseHandle(hFile);
}