// ?ReadFrameSizesFile@@YAPAKPAD@Z @ rva 0xac0e0 (160 B) — FileSize ->
// VDOAlloc -> LibOpen/LibRead/LibClose (sibling OpenVDOFile.c shape);
// vdoExitCode: 3 = VDOAlloc failed, 4 = short read OR open failure
// (open-fail falls through the handle guard with rd==0 != n); -1 =
// FileSize failure (no store) and alloc-failure paths; success returns
// the buffer pointer.
extern long __cdecl FileSize(char *name);
extern long __cdecl VDOAlloc(long size);
extern void __cdecl VDOFree(void *p);
extern short __fastcall LibOpen(char *name, int mode);
extern long __cdecl LibRead(short fh, void *buf, long n);
extern void __cdecl LibClose(short fh);
extern short vdoExitCode;

void *__cdecl ReadFrameSizesFile(char *name)
{
    long n = FileSize(name);
    void *buf;
    long rd;
    short fh;
    if (n == -1)
        return (void *)0;
    buf = VDOAlloc(n);
    if (!buf) {
        vdoExitCode = 3;
        return (void *)0;
    }
    rd = 0;
    fh = LibOpen(name, 1);
    if (fh != -1) {
        rd = LibRead(fh, buf, n);
        LibClose(fh);
    }
    if (rd != n) {
        vdoExitCode = 4;
        VDOFree(buf);
        return (void *)0;
    }
    return buf;
}