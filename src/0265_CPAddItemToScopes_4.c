/*
 * w44D_3d960_v1.c — @CPAddItemToScopes@4 @ 0x43d960 (144 B, fpo/esp)
 * Fastcall(WORD id in cx).  w = si home.  Three cdecl probe calls
 * (w, result->al) each gated, firing a 5-arg stdcall action with
 * targetV/ifmHandle interior pointers.  Third path reads a BYTE out
 * param from the local dword's high byte and, when set, clears both
 * goalP+0x18 and ifmHandle+0xc8.
 */
extern char targetV[];
extern char ifmHandle[];
extern char goalP[];

extern unsigned char __cdecl w44dS9f0(unsigned short a);
extern unsigned char __cdecl w44dSCa0(unsigned short a);
extern unsigned char __cdecl w44dSDb0(unsigned short a);
extern void __stdcall w44dSG(char *a, char *b, unsigned short c, int d, int e);
extern void __stdcall w44dSH(char *a, char *b, unsigned short c, unsigned char *d, int e);

void __fastcall CPAddItemToScopes(unsigned short id)
{
    unsigned short w = id;
    unsigned char b;

    if (w44dS9f0(w))
        w44dSG(targetV + 0xd8, targetV + 0x1c30, w, 0, 0);
    if (w44dSCa0(w))
        w44dSG(targetV + 0xd8, targetV + 0x1c30, w, 0, 1);
    if (w44dSDb0(w)) {
        w44dSH(ifmHandle + 0xd4, ifmHandle + 0x1c2c, w, &b, 0);
        if (b) {
            *(int *)(goalP + 0x18) = 0;
            *(int *)(ifmHandle + 0xc8) = 0;
        }
    }
}
