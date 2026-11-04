/* _Read@12 @ rva 0xa9f80 (dec 696192), size 0x80 — CRT low-level read
 * wrapper (FA.SMS Read). h = (short)arg1 into handles32[h]; fail path
 * sets _dosError = 0xffff; ReadFile(slot, buf, len, &nread, 0);
 * on ReadFile()==1 && nread==len -> _dosError = 0, return len else fail.
 */
extern void *handles32[];
extern unsigned short dosError;
__declspec(dllimport) unsigned long __stdcall ReadFile(void *, void *,
                                                        unsigned long,
                                                        unsigned long *,
                                                        void *);

unsigned long __stdcall Read(short h, void *buf, unsigned long len)
{
    unsigned long n;
    void *slot = handles32[h];
    if (slot == 0) {
        dosError = 0xffff;
        return 0xffffffff;
    }
    if (ReadFile(slot, buf, len, &n, 0) == 1 && n == len) {
        dosError = 0;
        return len;
    }
    dosError = 0xffff;
    return 0xffffffff;
}