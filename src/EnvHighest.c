/* @EnvHighest@4 @ rva 0x9b4f0 — patch-hybrid (tier-0/Tier-3): plain C + 10
 * same-length patches (no resaves): env entry scan; entries are 6 B wide,
 * value at entry+2, head count at caller's frame (c-8 base, count at -6).
 * Returns the entry whose 32-bit value at +2 is highest (else 0).
 *
 * FA roles: res=eax, best=esi, cursor=edi, scratch=edx, 3n=ebx — CL's /O2
 * /G5 plan is role-SWAPPED (best=edi, cursor=edx, val=esi) and normalizes
 * the compare to its canonical direction (val,best)/jle where FA streams
 * cmp best,val / jge. CL operand mirroring does not steer it (v1-v3).
 * All 10 patches are byte-replaces at the SAME length (no shift), so the
 * branch disp values are FA's own:
 * patch 0x7:  region 0x7..0x17 push edi/mov esi,-1/movsx edx,[ecx-6]/lea
 *             ebx,[edx+edx*2]/lea edi,[ecx+ebx*2-6] (17 B in, 17 B out).
 * patch 0x18: cmp edi,ecx / 72 12 jb (4 B).
 * patch 0x1c: mov edx,[edi+2] (3 B).
 * patch 0x1f: cmp esi,edx (2 B);  0x21: jge skip 7d 04 (2 B);
 * 0x23: mov esi,edx (2 B);  0x25: mov eax,edi (2 B);
 * patch 0x27: sub edi,6 -> 83 ef 06 8b-sub form (3 B);  0x2a: cmp edi,ecx
 * (2 B);  0x2c: jae L 73 ee (2 B). No relocs anywhere in the chunk.
 *
 * probes: v1-v3 (no: role swap + compare direction), v4 (role-mirrored C
 *   whose CL plan matches FA outside the swapped regs) — run: python3
 *   build/survey/hybrid_probe.py build/survey/probes/tier0_r7.json
 *   (EnvHighest_v4h EXACT).
 *
 * entry JSON for tools/swap.json:
 *   {"rva": 636144, "obj": "EnvHighest", "src": "src/EnvHighest.c",
 *    "maps": [],
 *    "patch": ["0x7,17,57beffffffff0fbf51fa8d1c528d7c59fa",
 *              "0x18,4,3bf97212", "0x1c,3,8b5702", "0x1f,2,3bf2",
 *              "0x21,2,7d04", "0x23,2,8bf2", "0x25,2,8bc7",
 *              "0x27,3,83ef06", "0x2a,2,3bf9", "0x2c,2,73ee"]}
 */
char *__fastcall EnvHighest_m(char *c)
{
    char *res = 0;
    long best = -1;
    char *e;
    long f;
    c = c + 8;
    e = c + *(short *)(c - 6) * 6 - 6;
    while (e >= c) {
        f = *(long *)(e + 2);
        if (best < f) {
            best = f;
            res = e;
        }
        e = e - 6;
    }
    return res;
}