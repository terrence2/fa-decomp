extern char curThing[];
extern char curThingType[];
int __stdcall COMinSpeed(void)
{
    if (*(char *)curThing == 4)
        return *(short *)(curThing + 0x23f);
    return *(short *)(curThingType + 0x67);
}
