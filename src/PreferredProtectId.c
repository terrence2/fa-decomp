// _PreferredProtectId@0 @ rva 0x636e0 (407264, 42 B code + 6 B pad) —
//   ushort return; dword flags at _curThing+0xf0 re-read per guard: bit30
//   clear -> xor ax,ax/ret; bit31 set -> mov ecx,eax and tail-jmp the
//   fastcall helper (unnamed chunk 0x45dc60 = $FA$_t_45dc60); bit31 clear
//   -> mov ax,word [re-read] (66 a1)/ret.
//   Old wall: C evaluates the second read as 8b 0d + f7 c1 (CL keeps the
//   flag in ecx; FA's a9 test form and a1/mov ecx,eax dance unreachable
//   in plain C) — w14a probes.
// patch-hybrid (survey tier-1 ppi_v4, 5 patches): v4 caches read2 in a
//   non-volatile f so the helper arg reuses eax (FA 8b c8); CL still
//   streams 8b 0d/f7 c1 and a straight e9 — patches convert the
//   accumulator forms CL cannot spell:
//   patch 0x0: 8b 0d <flags> -> a1 <flags> (FA moffs load into eax),
//     DIR32 at site 1.
//   patch 0x5: f7 c1 00 00 00 40 -> a9 00 00 00 40 (test eax,imm — FA's
//     a9 accumulator form).
//   patch 0x10: f7 c1 <imm 0x80000000> -> a1 <flags>/a9 <imm 0x80000000>
//     (re-insert FA's per-guard a1 re-load + a9), DIR32 at site 0.
//   patch 0x1a: 74 05 -> 74 07 (je disp: FA skip target is past the
//     re-inserted 8b c8).
//   patch 0x1c: insert 8b c8 (mov ecx,eax) before the e9 tail-jmp — FA
//     materializes the helper's fastcall arg in ecx explicitly.
//
// probes: build/survey/probes/t1_ppi_v1..v4.c (_v4 EXACT via patch; v1-v3
//   plain C walls) — run: python3 tools/fitobj.py build/survey/probes/t1_ppi_v4.obj
//   407264 --map '_ppiFlagsX=_curThing+0xf0'
//   --map '@PrefHelper_q@4=$FA$_t_45dc60'
//   --patch '0x0,6,a100000000,1:6:_ppiFlagsX' --patch '0x5,6,a900000040'
//   --patch '0x10,6,a100000000a900000080,0:6:_ppiFlagsX'
//   --patch '0x1a,2,7407' --patch '0x1c,0,8bc8'
//
// maps VERBATIM plus NEW: "_ppiFlagsX=_curThing+0xf0";
//   "@PrefHelper_q@4=$FA$_t_45dc60" already present.
// entry: add "patch": ["0x0,6,a100000000,1:6:_ppiFlagsX",
//   "0x5,6,a900000040", "0x10,6,a100000000a900000080,0:6:_ppiFlagsX",
//   "0x1a,2,7407", "0x1c,0,8bc8"]
extern volatile unsigned long ppiFlagsX;
extern unsigned short __fastcall PrefHelper_q(unsigned long f);

unsigned short PreferredProtectId_q(void)
{
    unsigned long f = ppiFlagsX;
    if (!(f & 0x40000000UL))
        return (unsigned short)0;
    if (f & 0x80000000UL)
        return PrefHelper_q(f);
    return (unsigned short)ppiFlagsX;
}