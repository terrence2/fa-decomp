// ?OpenVDOFile@@YAFPAD@Z @ rva 0xac090 (32 B) — FA asm: mov edx,1 /
//   mov ecx,[esp+4] / call @LibOpen@8 (fastcall: name in ecx, mode 1 in
//   edx) / 66 3d ff ff / 75 09 (jne skips the fail store) /
//   66 c7 05 <vdoExitCode> 04 00 / ret — opens a VDO file through LibOpen
//   and, on the -1 handle, sets the short vdoExitCode to 4; returns the
//   handle still in ax (short return, no reload — FileSize carries the
//   matching exit-code store). The 66 3d ff ff cmp-imm16 form comes from
//   `fh == -1` on the SHORT local (the 0xffff spelling movzx's + 81 f9 —
//   probe b19c_vdo_b exact, b19c_vdo_a rejected).
extern short __fastcall LibOpen(char *name, int mode);
extern short vdoExitCode;

short __cdecl OpenVDOFile(char *name)
{
    short fh = LibOpen(name, 1);
    if (fh == -1)
        vdoExitCode = 4;
    return fh;
}