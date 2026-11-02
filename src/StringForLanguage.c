// @StringForLanguage@8 @ rva 75856 (0x12850, 64 B) — patch-hybrid.  The
//   plain-C body (FA semantics are in terms of DST: p = strchr(dst, ';');
//   if (!p) p = Strend(dst); n = p - dst; memmove(dst, src, n); dst[n] = 0;
//   dst-first first-decl parks CL to FA's 8b da (ebx=src) / 8b f9 (edi=dst))
//   reproduces 49/52 compiled bytes; the 3 remaining bytes are (a) CL's
//   memmove arg push order esi,ebx,edi (56 53 57 at 0x22-0x23) vs FA's
//   esi,edi,ebx (56 57 53) and (b) the dd[n] store sib (CL 37 = [edi+ebx*1]
//   vs FA 1e = [esi+ebx*1] in c6 04 1e 00) — CL parks dst in edi at the
//   store site but FA holds dst in esi there.  Patch-hybrid is the minimal
//   3x1-byte same-length fix; CL 75 3b push/imm8 shape, call sites and the
//   FA 05 00000000 + 8d a4 24 00000000 trailer pad are census-clean.
//   Probe build/survey/probes/p_w23_StringFL_final.obj EXACT (w23_r8.json;
//   ladder was w23_StringFL_v1..v5, r4/r6).
//   Maps (swap.json verbatim): [].
//   Patches: "34,1,57", "35,1,53", "46,1,1e".
extern char *strchr(const char *s, int c);
extern void *memmove(void *d, const void *s, unsigned long n);
extern char *__fastcall Strend(char *s);

void __fastcall StringForLanguage_q(char *dst, char *src)
{
    char *dd = dst;
    char *sb = src;
    char *p;
    unsigned long n;
    p = strchr(dd, 0x3b);
    if (!p)
        p = Strend(dd);
    n = p - dd;
    memmove(dd, sb, n);
    dd[n] = 0;
}