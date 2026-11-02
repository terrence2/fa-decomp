// _GRPInit@0 @ rva 0x5e7c0 (387008, 36 B code + 12 B pad) — GRPInit twin
//   of WNGInit: memset(groupIds, 0, 0xc8) inlined as rep stosd, followed
//   by the groupSizes dword/word store pair. Naked-asm escape (same
//   family). EXACT as plain C + 2 patches (survey tier-1; identical to the
//   WNGInit fit): constant-size memset -> CL inline rep stosd with the
//   early pop edi CL emits and the 66 a3 word store that FA spells through
//   ecx = groupSizes as 66 89 41 08 with the pop deferred.
//   patch 0xf: delete CL's early 5f (pop edi).
//   patch 0x19: replace CL[0x19,0x20) with FA's 11 B
//     b9 <groupSizes>/5f/66 89 41 08/c3, DIR32 attached at site 1.
//
// probes: build/survey/probes/t1_grpinit_v1.c (EXACT via patch) — run:
//   python3 tools/fitobj.py build/survey/probes/t1_grpinit_v1.obj 387008
//   --patch '0xf,1,' --patch '0x19,7,b9000000005f66894108c3,1:6:_groupSizes'
//
// maps VERBATIM: [] (groupIds/groupSizes resolve identity)
// entry: add "patch": ["0xf,1,", "0x19,7,b9000000005f66894108c3,1:6:_groupSizes"]
#include <string.h>
extern char groupIds[];
extern long groupSizes[];

void GRPInit_q(void)
{
    memset(groupIds, 0, 0xc8);
    groupSizes[0] = 0;
    groupSizes[1] = 0;
    {
        short *gs = (short *)groupSizes;
        gs[4] = 0;
    }
}