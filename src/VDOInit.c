// ?VDOInit@@YIXXZ @ rva 0x5250 (32 B) — FA asm: a0 <videoInitialized>/
//   84 c0 (test al)/75 0x15 (jne straight to ret)/66 c7 05
//   <vdoColorProcess>,0 (WORD zero-store, disp = the FA-obj DIR32 reloc
//   against ?vdoColorProcess@@3FA)/e8 _BuildSelfModifyCode@0/c6 05
//   <videoInitialized>,1/c3.  __fastcall void(void): if video has not
//   initialized, zero the self-modify area's first word, build the
//   self-modify code, set videoInitialized = 1 (inside the branch — the
//   jne skips all three and the ret).  Plain C with a *dis.py elision
//   caveat*: dis.py's listing dropped the c7/c6 stores (raw FA bytes
//   checked directly).  Probe build/w4probe/b20f_VDOInit.obj — exact
//   modulo fixup dwords.
extern char videoInitialized;    /* ?videoInitialized@@3DA */
extern char vdoColorProcess[];   /* ?vdoColorProcess@@3FA */

extern void __stdcall BuildSelfModifyCode(void);

void __fastcall VDOInit_q(void)
{
    if (!videoInitialized) {
        *(unsigned short *)vdoColorProcess = 0;
        BuildSelfModifyCode();
        videoInitialized = 1;
    }
}