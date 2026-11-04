// @WPDoingWaypoints@0 @ rva 0x97b00 — char return via al only (b0 01 / 32 c0,
//   probe d62; an int return emits b8/33c0 32-bit forms, d61).
extern char curThing[];

char WPDoingWaypoints_q(void)
{
    long p = *(long *)((char *)curThing + 0xe8);
    if (p && !(*(char *)p & 2))
        return 1;
    return 0;
}
