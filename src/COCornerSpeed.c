extern char curThing[];
extern char curThingType[];
int __stdcall COCornerSpeed(void)
{
    if (*(char *)curThing == 4)
        return *(short *)(curThing + 0x241);
    return *(short *)(curThingType + 0x6b);
}
