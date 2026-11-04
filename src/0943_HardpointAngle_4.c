/* @HardpointAngle@4 @ rva 0xa86b0 (112 B) — v2: angle sourced from the
 * out local (FA reloads [esp+4] into eax then mov si,[eax+6]); r (call
 * return) stays in eax for the test/mov-cl/cmp-7 check, so no pointer
 * local is needed except *r == 7's load. */
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
                angle = *(unsigned short *)((char *)out + 6);
            else
                angle = 0;
        } else
            angle = 0;
    } else
        angle = 0;
    PutCurObj();
    return angle;
}