/* @HardpointAngle@4 @ rva 0xa86b0 (112 B) — fastcall short(int obj):
 * if the word at ?shapeId@@3GA is zero, return 0 without touching the
 * cur-obj pair; else GetCurObj(shapeId[0]), check _curThing (2 or 4),
 * byte at _curThingType+0xb5 > obj, HARDPtrs(obj, &out, 0) with
 * *(char*)r == 7 => angle = (short)[r+6]; PutCurObj(); return angle.
 * angle lives in esi (shared with the incoming obj after its last use). */
extern volatile short w34E_shapeId[];    /* =?shapeId@@3GA */
extern char curThing;                    /* =_curThing */
extern char curThingType[];              /* =_curThingType */
extern void __fastcall GetCurObj(unsigned short id);   /* =@GetCurObj@4 */
extern void __fastcall PutCurObj(void);                /* =@PutCurObj@0 */
extern char *__stdcall HARDPtrs(int obj, void *out, void *zero);   /* =_HARDPtrs@12 */

unsigned short __fastcall HardpointAngle(int obj)
{
    unsigned short angle;
    int out;
    char *r;
    long v;

    if (w34E_shapeId[0] == 0)
        return 0;
    GetCurObj(w34E_shapeId[0]);
    if (curThing == 2 || curThing == 4) {
        v = (unsigned char)curThingType[0xb5];
        if (v > obj) {
            r = (char *)HARDPtrs(obj, &out, 0);
            if (r != 0 && *r == 7)
                angle = *(unsigned short *)(r + 6);
            else
                angle = 0;
        } else
            angle = 0;
    } else
        angle = 0;
    PutCurObj();
    return angle;
}