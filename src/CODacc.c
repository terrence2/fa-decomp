extern char curThing[];
extern char curThingType[];
int __stdcall CODacc(void)
{
    if (*(char *)curThing == 4)
        return *(long *)(curThing + 0x253);
    return *(long *)(curThingType + 0x71);
}
