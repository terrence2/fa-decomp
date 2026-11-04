/* __open_osfhandle @ rva 0xdece0 (180 B) — FPO/esp, params 2.
 * Semantics: builds fmode bits from osfhandle flag bytes (0x8 -> 0x20,
 * ah&0x40 -> 0x80), GetFileType(handle): 0 -> dosmaperr(GetLastError),
 * return -1; 2 -> |0x40; 3 -> |0x8; alloc_osfhnd(): -1 -> errno=EMFILE(0x18),
 * doserrno stub sets *p=0, return -1; else set_osfhnd(fh, handle),
 * or bl|1, lock row (edx=pio[eax>>3 & ~1... _crtheap+4] row table),
 * store bl at row[0x4], unlock_fhandle(fh), return fh.
 * Transplant entry — verbatim FA body, zeroed imms re-added as newsites. */
extern int __cdecl dosmaperr(int e);   /* TO __dosmaperr */
extern int * __cdecl errnoint(void);
static int fh_hack;
int __cdecl w44h_open_osfhandle(long osfhandle, int flags)
{
    unsigned m = 0;
    if (osfhandle & 8) m |= 0x20;
    if (osfhandle & 0x4000) m |= 0x80;
    fh_hack = (int)m + flags;
    return fh_hack ? -1 : -2;
}
