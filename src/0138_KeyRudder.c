/*
 * w44D_17aa0_v2.c — switch spelling (v1: CL kept 16-bit cmps + xor/a3 stores)
 * ?KeyRuddy@@YAGFG@Z @ 0x417aa0 (112 B)
 * v2 spelling: `rudder` (no leading underscore — CL 4.2 doubles "_x" idents
 * to "__x"; FA public is _rudder, reached by identity).
 */
extern long rudder;
extern unsigned char keyarray[];

unsigned short __cdecl KeyRudder(short a, unsigned short b)
{
    int v = a;
    switch (v) {
    case 0:
        rudder = 0;
        return 0;
    case 2:
        if (keyarray[0x4f]) { rudder = -256; return 0; }
        if (keyarray[0x51]) { rudder = 1; return 0; }
        rudder = 0;
        return 0;
    case 3:
        return b;
    }
    return 0;
}