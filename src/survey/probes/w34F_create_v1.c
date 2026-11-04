extern unsigned short dosError;
__declspec(dllimport) long __stdcall CreateFileA(char *, unsigned long, unsigned long, void *, unsigned long, unsigned long, unsigned long);
__declspec(dllimport) int __stdcall CloseHandle(long);
extern short __fastcall get16_(void *);

short __fastcall w34f_create(char *path)
{
    long h;
    short r;
    if (path == 0) {
        dosError = 0xffff;
        return -1;
    }
    dosError = 0;
    h = CreateFileA(path, 0xC0000000, 0, 0, 2, 0x80, 0);
    if (h == -1) {
        dosError = 0xffff;
        return -1;
    }
    r = get16_(h);
    if (r == -1) {
        dosError = 0xffff;
        CloseHandle(h);
        return -1;
    }
    return r;
}