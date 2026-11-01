// ?FileSize@@YAJPAD@Z @ rva 0xabf00 (32 B) — FA asm: mov eax,[esp+4] /
//   push eax / call _LibFileSize (cdecl wrapper: LibFileSize(name)) /
//   add esp,4 / 83 f8 ff / 75 09 (jne skips the fail store) /
//   66 c7 05 <vdoExitCode> 04 00 — on LibFileSize's -1 the VDO layer's
//   exit code is set to a WORD 4 (vdoExitCode is ?vdoExitCode@@3FA, the
//   short exit-code slot shared by OpenVDOFile) / ret. Plain C exact
//   (probe b19c_fs; tail = census 8d 64 24 00).
extern long LibFileSize(char *name);
extern short vdoExitCode;

long __cdecl FileSize(char *name)
{
    long r = LibFileSize(name);
    if (r == -1)
        vdoExitCode = 4;
    return r;
}