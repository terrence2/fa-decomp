// 0xb84b0 (unnamed, 16 B) — mov dword [curThing+0x34], 0; ret — v1
extern char curThingB[];

void __cdecl w27b_st34(void)
{
    *(long *)(curThingB + 0x34) = 0;
}