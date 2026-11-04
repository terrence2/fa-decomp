/* Transplant husk (whole-body patch) for @GetDosFileTime@12, rva 495136 (0x78e20), 144 B.
 * FA semantics (dis.py 0x78e20): fastcall@12 (ecx=path, edx=&ret, ret in bl):
 *   h = CreateFileA(path, 0x80000000, 1, NULL, 3, 0, NULL);   // via ff15 [IAT]
 *   if (h == INVALID_HANDLE_VALUE) return 1;
 *   r = GetFileTime(h, NULL, NULL, &ft);                       // call ebp ([[IAT]] loads)
 *   if (r && FileTimeToLocalFileTime(&ft, &lft))               // call ebp
 *     r = bl = FileTimeToDosDateTime(&lft, (u16*)edx, (u16*)edx); // call ebx
 *   CloseHandle(h); return bl;
 * CL /O2 won't reload the 3 IAT pointers into regs (mov ebp,[__imp__X]); it calls ff15
 * direct — body fully patched over husk.
 */
void __fastcall GetDosFileTime(long a, long b, long c) { (void)a; }