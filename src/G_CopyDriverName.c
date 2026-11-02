// @G_CopyDriverName @ rva 619232 (0x972e0, 48 B) — patch-hybrid.  The
//   plain-C body (inline strlen/strcpy expansion with the intrinsic kept
//   ON: mov edi,imm dst / f2 ae repne scasb / not ecx / sub edi,ecx =
//   strlen, then the dword rep movsd + odd-byte rep movsb tail) reproduces
//   27/43 compiled bytes; the remaining walls: (1) CL parks the post-scas
//   byte-count materialization in eax (`8b c1` mov eax,ecx at 21) where FA
//   parks it in edx (`8b d1`) and keeps it there across the rep so the odd
//   tail is `8b ca` mov ecx,edx — CL's counterpart is `8b c8` mov ecx,eax
//   (1-B modrm fix); (2) CL loads the src ptr [esp+0xc] straight into edi
//   (`8b 7c 24 0c`) and reuses eax for the tail reload, FA loads it into
//   eax first then `8b f8` mov edi,eax — 2-B modrm + instruction-order
//   resynthesis of the whole 16-B tail; (3) FA carries a 3-B `8d 49 00`
//   trailer pad CL never emits.  Patch-hybrid replaces the 16-B tail and
//   fixes the 1 modrm byte.
//   Probe build/survey/probes/p_w23_GCopyDriver_patch2.obj EXACT
//   (w23_r3.json; ladder w23_GCopyDriver_v1/patch, w23_GCopyDriver_fO1).
//   Maps (swap.json verbatim + patch site): _driverNameBuf_=_clipHeight+0x8.
//   Patches: "21,1,d1",
//            "27,16,8b44240c8bf8f3a58bca83e103f3a45f5ec38d4900".
extern char driverNameBuf_[];
char *strcpy(char *d, const char *s);

void G_CopyDriverName_q(char *dst)
{
    strcpy(dst, driverNameBuf_);
}