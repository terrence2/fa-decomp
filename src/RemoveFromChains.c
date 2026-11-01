extern char curThing[];
extern char chainStart[];
extern char serviceTicks[];
extern void __fastcall chainClear_(int ctx);
void __stdcall RemoveFromChains(void)
{
    if (*(long *)(curThing + 1) & 2)
    {
        chainClear_((int)chainStart);
        chainClear_((int)(serviceTicks + 8));
    }
}
