/* ?socket_set_state_func@@YAXPAUsocket_state@@P6ADIJH0@ZW4SOCK_STATE@@@Z
 * @ rva 0xa31c0 (dec 668096), size 0x20 — EXACT, C + 1 patch.
 *
 * C recipe: plain long-pointer stores to +0x1c and +0x10 (v2 statement
 * order = FA's store order). The 5-byte ILINK e9+0x9 tail jmp into the
 * following gap chunk ($FA$_t_4a31e0) is not C-formable at the tail of a
 * 0x17-byte body — inserted by patch with a REAL32 site attached, target
 * mapped to FA's gap-chunk stub symbol; FA's other prologue bytes in the
 * tail (mov edi,edi + lea esp,[esp+0]) are census fillers.
 *
 * patch provenance: patch 0x12 (ILINK e9 self-jmp tail into gap chunk):
 * toolchain-diff — inserted FA's e9 +4B tail jmp with a REL32 site mapped
 * to $FA$_t_4a31e0; CL drops the tail jmp (ret-only epilogue).
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_socket_set_state_func_v2.obj 668096 \
 *   --patch '0x12,1,e900000000,1:20:_tailjmp' --map '_tailjmp=$FA$_t_4a31e0' \
 *   build/survey/probes/w24a_socket_set_state_func_v2_fit.obj
 * (tail = census-proven filler 8bff+8da42400000000.)
 */
void socket_set_state_func(void *s, long f, long st)
{
    *(long *)((char *)s + 0x1c) = f;
    *(long *)((char *)s + 0x10) = st;
}

/* newsite tail-jmp target: patch 0x12 attaches a REL32 site to symbol
 * _tailjmp (mapped to $FA$_t_4a31e0); declared here so from_sweep --objcheck
 * sees the C spelling (CL emits nothing for the unused declaration). */
extern void tailjmp(void);
