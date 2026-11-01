// _MaxGAtAlt@0 @ rva 0x9b4b0 (64 B) — FA asm: push esi / push edi / movsx esi,
// [curThingType+0xc4] (alt) / a1 mov edi,[curThing+0x15] / sar edi,8 (top) /
// loop: fastcall GetFlightEnvelope(alt) -> EnvHighest (tail-jmp chain keeps
// esi/edi alive), cmp [eax+2],edi / jge done / dec esi / jg loop / ret esi.
// Plain C while-loop matched CL's esi/edi loop plan and the fastcall chain
// exactly (probe b17c_maxgatalt_v1 byte-exact — the sar>>8 shift and
// `alt = alt - 1` decrement both reproduce; a `--alt` variant would be the
// same, v1 form chosen). Addends +0xc4 / +0x15 live in the C expressions;
// all four externs identity, no maps.
extern char curThingType[];
extern char curThing[];
extern char * __fastcall GetFlightEnvelope(int alt);
extern char * __fastcall EnvHighest(char *env);

int __stdcall MaxGAtAlt(void)
{
    int alt = (int)*(short *)(curThingType + 0xc4);
    int top = *(long *)(curThing + 0x15) >> 8;
    while (alt > 0) {
        if (*(long *)(EnvHighest(GetFlightEnvelope((long)alt)) + 2) >= top) break;
        alt = alt - 1;
    }
    return alt;
}