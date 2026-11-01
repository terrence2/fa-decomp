// ?printPoly@@YAXHPAUTVERTEX@@@Z @ rva 0x96cb0 (16 B, FPO fpo/esp
// params=2 dwords) — FA's printPoly body is a bare ret (c3); the 15-B
// lea-esp tail run is FA's own boundary filler, appended by fitobj as a
// census-proven composition. Empty cdecl body emits exactly the c3.
struct VERTEX;
void printPoly(int a, struct VERTEX *v)
{
}