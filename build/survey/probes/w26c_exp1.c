// cmp-orientation experiments (dump only, no fitobj)
typedef struct { unsigned char pad[2]; unsigned short id; } O26E;
extern unsigned short w26_curId2;

void __fastcall e1(O26E *o)
{
    if (o->id != w26_curId2) { o->pad[0] = 1; }
}

void __fastcall e2(O26E *o)
{
    if (w26_curId2 != o->id) { o->pad[0] = 1; }
}

void __fastcall e3(O26E *o)
{
    unsigned short i = o->id;
    if (i != w26_curId2) { o->pad[0] = 1; }
}

void __fastcall e4(O26E *o)
{
    unsigned int i = o->id;
    if (i != w26_curId2) { o->pad[0] = 1; }
}

void __fastcall e5(O26E *o)
{
    if (o->id == w26_curId2) { o->pad[0] = 1; }
}