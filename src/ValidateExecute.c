// ?_ValidateExecute@@YAHP6GHXZ@Z @ rva 0xdf4c0 (914624, 27 B) — cdecl
//   int(VEP pfn): eax = pfn ([esp+4]); push esi; esi = 1; push eax; ff 15
//   __imp__IsBadCodePtr@4; test eax; je +2 (skips ONLY the xor esi,esi);
//   xor esi,esi; mov eax,esi; pop esi; ret. The old naked note: fam-d
//   "call-through-register mov ebp,[imp]; call ebp" wall.
// patch-hybrid (survey tier-1 valexe_v3, 3 patches): plain flag-variable C
//   hits esi=1/test/je-skips xor exactly; CL's only deltas are the fam-d
//   ebx bookend and the esi-init/arg-push interleave:
//   patch 0x4: replace CL[4,7) '53 56 50' (push ebx/push esi/push eax) with
//     FA's push esi / mov esi,1 / push eax interleave (7 B
//     56be0100000050) — root-caused: FA streams the esi init BETWEEN the
//     callee-save and the arg push; CL orders pushes first, init after.
//   patch 0xb: delete CL's mov esi,1 (5 B, now redundant duplicate).
//   patch 0x1a: delete CL's 5b pop ebx (fam-d dllimport bookend; FA has
//     none — the old wall was only the ebx reservation, and this decl
//     shape needs no ebx at all once the bookends are removed).
//
// probes: build/survey/probes/t1_valexe_v1.c (no), _v2.c (no), _v3.c
//   (EXACT via patch) — run: python3 tools/fitobj.py
//   build/survey/probes/t1_valexe_v3.obj 914624 --patch
//   '0x4,3,56be0100000050' --patch '0xb,5,' --patch '0x1a,1,'
//
// maps VERBATIM: _impIsBadCodePtr=__imp__IsBadCodePtr (vestigial — the
//   dllimport decl emits __imp__IsBadCodePtr directly).
// entry: add "patch": ["0x4,3,56be0100000050", "0xb,5,", "0x1a,1,"]
__declspec(dllimport) int __stdcall IsBadCodePtr(void (__stdcall *pfn)(void));
typedef void (__stdcall *VEP)(void);

int __cdecl _ValidateExecute_q(VEP pfn)
{
    long r = 1;
    if (IsBadCodePtr((VEP)pfn))
        r = 0;
    return r;
}