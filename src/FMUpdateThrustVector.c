// _FMUpdateThrustVector@0 @ rva 0x50ca0 (48 B) — three right-to-left
// _MatchF24@12 (stdcall, no cleanup) args: type<<8 = movsx word
// curThingType+0x15f then shl 8 (pushed first = arg3), mfa<<8 = movsx
// word curThing+0x1fa shl 8 (arg2), string at curThing+0x1f6 pushed as
// imm (68, arg1). Probe w14a_fmtv1 byte-exact, identity externs.
extern char curThing[];
extern char curThingType[];
extern int __stdcall MatchF24(int a, int b, int c);

int FMUpdateThrustVector(void)
{
    return MatchF24((int)(curThing + 0x1f6),
                    ((long)(*(short *)(curThing + 0x1fa))) << 8,
                    ((long)(*(short *)(curThingType + 0x15f))) << 8);
}