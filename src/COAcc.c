extern char curThing[];
extern char curThingType[];
int __stdcall COAcc(void)
{
    if (*(char *)curThing == 4)
        return *(long *)(curThing + 0x247);
    return *(long *)(curThingType + 0x6d);
}
