// @DialogDraw@4 @ rva 550288 (0x86590, 32 B) — patch-hybrid.  The plain-C
//   body (fp = *(fn-ptr**)(p+6), call through local fn-ptr var, Push/Pop
//   wrapped) reproduces 27/32 bytes; the 5 remaining bytes are the arg-park
//   register mirror (CL `mov eax,[esp+4]` 44 at 0x6 vs FA `mov ecx,[esp+4]`
//   4c; push eax 0x50/0x12 call ff d1 vs FA push ecx 0x51 / call ff d0, plus
//   the matching modrm bytes 48->41 at 0xa and c9->c0 at 0xd).  Flag axis
//   (/G3, /Gd) does NOT steer these — same 5 diffs.  Patch-hybrid is the
//   minimal 5x1-byte same-length fix.
//   Probe build/survey/probes/p_w23_DialogDraw_patch.obj EXACT (w23_r2.json).
//   Maps (swap.json verbatim): _PushShellAlloc@0=?PushShellAlloc@@YGXXZ,
//   _PopShellAlloc@0=?PopShellAlloc@@YGXXZ.
//   Patches: "6,1,4c", "10,1,41", "13,1,c0", "16,1,51", "18,1,d0".
extern void __stdcall PushShellAlloc(void);
extern void __stdcall PopShellAlloc(void);

void __stdcall DialogDraw_q(void *p)
{
    void (__cdecl *fp)(void *);
    PushShellAlloc();
    fp = *(void (__cdecl **)(void *))((char *)p + 6);
    if (fp)
        fp(p);
    PopShellAlloc();
}