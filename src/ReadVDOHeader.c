// 0xac0b0 ?ReadVDOHeader@@YADFPAUVDOHEADER@@@Z (48 B) — v1
extern long __cdecl LibReadq(short idx, void *dst, long max);
extern short vdoExitCodeQ;

char __cdecl ReadVDOHeaderq(short idx, char *hdr)
{
    long n;

    n = LibReadq(idx, hdr, 0x30);
    if (n != 0x30)
        vdoExitCodeQ = 4;
    return (char)(n == 0x30);
}