/* G_UPolygonFlip - FA rva 0x96620 (615968) - EXACT probe verdict, tier1_a_r2.json entry 'G_UPolygonFlip_v2'
 * Form: plain C
 * Levers: __fastcall callee decls (cdecl emitted 83 c4 08 arg cleanups)
 * Maps: _gFloatFlatFlip=@G_FloatFlatFlip@8, _gFlip=@G_Flip@8, _gUPolygon=@G_UPolygon@8
 * Probes: v1,v2
 */
extern char cFillType[];
extern char effects[];
extern int __fastcall gFloatFlatFlip(void *a, void *b);
extern int __fastcall gFlip(void *a, void *b);
extern int __fastcall gUPolygon(void *a, void *b);

void __fastcall G_UPolygonFlip(void *a, void *b)
{
    if (cFillType[0]) {
        if (*(int *)effects & 0x10000) {
            gFloatFlatFlip(a, b);
            return;
        }
    }
    gFlip(a, b);
    gUPolygon(a, b);
}
