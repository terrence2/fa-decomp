// _COMaxSpeed@0 @ rva 0x76d20 — push &_curThingType / push &_curThing /
//   call _MaxSpeed@8 / ret (probe w7_ms: CL emits push imm32 with DIR32
//   relocs for address-of-global args; stdcall callee cleans).
extern void __stdcall MaxSpeed(void *a, void *b);
extern int curThing;
extern int curThingType;

void __stdcall COMaxSpeed(void)
{
    MaxSpeed(&curThing, &curThingType);
}
