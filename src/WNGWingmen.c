// _WNGWingmen@8 @ rva 0x5dd10 (384272, 48 B) — stdcall(id, out):
//   if (out) *out = wingSizes[id] - 1; return wingIds + id*20 + 2.
//   FA: mov ecx,[esp+8]/test/je skip/xor edx/mov eax,[esp+4]/mov dl,
//   [wingSizes+eax]/dec edx/mov [ecx],edx/jmp cont/skip: mov eax,[esp+4]/
//   cont: shl eax,2/lea eax,[wingIds+eax*5+2]/ret 8.
// EXACT as plain C (survey tier-1 probe v1): the guarded store + shared
//   tail collapse from the two-statement C — FA's shl/lea chain is CL's
//   id*20+2 (lea eax*4+eax bakes the +2 addend); the byte load is the
//   uchar array decl; movzx twin spelling (v2) matched too. Maps
//   VERBATIM: [] (wingIds/wingSizes resolve identity).
//
// probes: build/survey/probes/t1_wngwm_v1.c (EXACT), t1_wngwm_v2.c
//   (EXACT) — run: python3 build/survey/hybrid_probe.py
//   build/survey/probes/tier1_re.json
extern unsigned char wingSizes[];
extern char wingIds[];

char *__stdcall WNGWingmen_q(long id, long *out)
{
    if (out)
        *out = (long)wingSizes[id] - 1;
    return (char *)(wingIds + id * 20 + 2);
}