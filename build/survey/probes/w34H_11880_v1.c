// _AngleOffNose@4 @ rva 0x11880 (112 B = 97 code + 15 census pad) --
// stdcall short(p): Angles(curThing+0x11, p, &s2, &s1) then
// s2 = Abs(s2 - *(short*)(curThing+0x1d)); s1 = Abs(s1 - *(short*)(curThing+0x1f));
// return s1 > s2 ? s1 : s2 (short in ax).
extern int __stdcall Angles(void*, void*, short*, short*);
extern int __fastcall Abs(short);
extern char curThing[];

short __stdcall AngleOffNose(void* p)
{
    short s1;
    short s2;
    Angles(curThing + 0x11, p, &s2, &s1);
    s2 = (short)Abs(s2 - *(short*)(curThing + 0x1d));
    s1 = (short)Abs(s1 - *(short*)(curThing + 0x1f));
    return s1 > s2 ? s1 : s2;
}