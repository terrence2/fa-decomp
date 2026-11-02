// _OBJTempAlias@0 @ rva 0x8f950 (588112, 31 B code + 1 B pad) — nextObjId+4
//   advance: pick ?COMMENT_TYPE@@3W4__unnamed@@A+0x85c (ctBase) when it is
//   below the old COMMENT_TYPE+0x860 (ctNext) value, else keep ctNext;
//   store selected+1 through the 89 0d store-from-ecx form; return the OLD
//   value (8b c1 copy before 41 inc ecx).
// CL C forms reorder the loads (nextObjId-first a1), fold the +1 into lea
//   ecx,[eax+1], use a3 stores and jle polarity — w12b variants; the
//   dead-increment 8b c1/41 dance was asm-only.
// patch-hybrid (survey tier-1 objalias_v4, 4 patches): the C gets every
//   opcode byte right; three structural deltas close by patch:
//   patch 0x0 / 0x5 (rewiring, zero-shift): CL a1-loads nextObjIdX and
//     8b 0d-loads ctNext860X — the opposite of FA (eax = ctNext at
//     COMMENT_TYPE+0x860, ecx = nextObjId at _nextObjId+0x4). Decl-order
//     variants (v5: a first, v6: single-var) do not move CL's choice. The
//     two dword sites are dropped inside identical-length patch payloads
//     and re-added with map ctNext860A / nextObjId4A. Without this the
//     preserved 3b c1 computes nextObj-ctNext — INVERTED predicate vs FA's
//     ctNext-nextObj — and both dwords resolve to the wrong VA at gate.
//   patch 0xd: CL's 7e 05 (jle, +5 — skips the base-load span of 5 B)
//     -> FA's 7d 06 (jge, +6 — skips 6 B: 8b 0d base load). Root-caused:
//     compare-polarity normalization — CL mirrors `if (a < b) b = c`
//     into jle; FA streams jge with the base load as fall-through.
//   patch 0xf: replace CL[0xf,0x17) — a1 <base> (5 B) + 8d 48 01 lea
//     ecx,[eax+1] (3 B) — with FA's 9 B: 8b 0d <base> (6 B) / 8b c1
//     (ret-value copy eax<-ecx) / 41 inc ecx; DIR32 attached at payload+2
//     (the imm dword — payload+1 anchors the 0d modrm byte and the addend
//     bake then writes over the opcode span). Root-caused: CL homes the
//     return-value constituent in eax (a1 base load + lea from eax); FA
//     homes it in ecx and copies to eax with 8b c1 before the increment.
//
// maps for the patch-site rewiring tokens (patch-level, no C decls exist):
//   "ctNext860A=?COMMENT_TYPE@@3W4__unnamed@@A+0x860",
//   "nextObjId4A=_nextObjId+0x4"
//
// probes: build/survey/probes/t1_objalias_v1..v4.c (_v4 EXACT via patch;
//   _v4 b-first decl order) — run: python3 tools/fitobj.py
//   build/survey/probes/t1_objalias_v4.obj 588112
//   --map '_ctNext860X=?COMMENT_TYPE@@3W4__unnamed@@A+0x860'
//   --map '_ctBase85cX=?COMMENT_TYPE@@3W4__unnamed@@A+0x85c'
//   --map '_nextObjIdX=_nextObjId+0x4'
//   --patch '0xd,2,7d06' --patch '0xf,8,8b0d000000008bc141,1:6:_ctBase85cX'
//
// maps VERBATIM (entry FROMs are the bare names; final srcs keep the probe
//   X-names, so add): "_ctNext860X=?COMMENT_TYPE@@3W4__unnamed@@A+0x860",
//   "_ctBase85cX=?COMMENT_TYPE@@3W4__unnamed@@A+0x85c",
//   "_nextObjIdX=_nextObjId+0x4"  (addend bake via map TO)
// entry: add "patch": ["0xd,2,7d06",
//   "0xf,8,8b0d000000008bc141,1:6:_ctBase85cX"]
extern long ctNext860X;
extern long ctBase85cX;
extern long nextObjIdX;

long OBJTempAlias_q(void)
{
    long b = nextObjIdX;
    long a = ctNext860X;
    long r;
    if (a < b)
        b = ctBase85cX;
    r = b;
    nextObjIdX = ++b;
    return r;
}