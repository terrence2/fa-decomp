// _SEQrun @ rva 0x46280 (287360 DEC; off 284288) (16 B) — EXACT winner
// (probe w24c_SEQrun_v1.c). Pure CL C, NO maps, NO patches, 0 relocs.
//
// FA body is a bare c3 ret + census pad (2x8d642400 + 8da42400000000,
// 15 B) — FA's own zero-body sequence runner (its FPO reports params=8 but
// the body is empty). Plain C empty void cdecl function reproduces it.
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_SEQrun_v1.obj 287360 \
//     build/survey/probes/w24c_SEQrun_v1_fit.obj
void SEQrun(void)
{
}