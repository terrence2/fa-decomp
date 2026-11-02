/* ?NET_WriteAvail@@YAJJ@Z @ rva 0xad240 (dec 709184), size 0x30 — EXACT,
 * C + 1 patch.
 *
 * C recipe: the a1 moffs read of ws (first byte test), single-exit
 * control flow with the failure path falling through to `return 0` last
 * (FA shape), validate_player as an unsigned long __cdecl call. The
 * sub-block register plan at 0x1a differs only in registers (FA: mov
 * ecx,[p+0x2c8e] / mov edx,[p+0x2c92] / sub ecx,edx / mov eax,ecx; CL:
 * mov edx,[p+0x2c92] / mov ecx,eax / mov eax,[p+0x2c8e] / sub eax,edx) —
 * same size, same encodings modulo regs/modrm; replaced by patch.
 *
 * patch provenance: patch 0x1a (sub-block register plan): toolchain-diff —
 * FA computes the availability delta in ecx then copies to eax; CL's
 * register plan (edx/ecx in different positions) yields the same 16 bytes
 * at different regs. Field disps +0x2c8e/+0x2c92 are plain displacement
 * bytes (not relocs) and match FA's.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_NET_WriteAvail_v3.obj 709184 \
 *   --patch '0x1a,16,8b888e2c00008b90922c00002bca8bc1' \
 *   --map '_ws_x=?ws@@3U_winsock_funcs@@A' \
 *   --map '_validate_player=?validate_player@@YAPAU_player_info@@J@Z' \
 *   build/survey/probes/w24a_NET_WriteAvail_v3_fit.obj
 * (2 relocs: DIR32 ws base (a1 moffs) + REL32 call validate_player.
 * tail = census-proven filler 8bff.)
 */
extern unsigned long __cdecl validate_player(long h);
extern unsigned char ws_x[];
long __cdecl NET_WriteAvail(long h)
{
    unsigned long p;
    if (!*(unsigned char *)ws_x)
        goto fail;
    p = (unsigned long)validate_player(h);
    if (!p)
        goto fail;
    return *(long *)((char *)p + 0x2c8e) - *(long *)((char *)p + 0x2c92);
fail:
    return 0;
}
