/* w32C mapwts v2: MAPWorldToScreen (rva 138944, 62 B, no pad)
 * FA (rva 0x21ec0): push esi; mov eax,[ecx] (wp[0]); mov esi,edx (sp);
 * sub eax,[wcX] (2b 05 moffs); cdq; idiv [mapScale] (f7 3d moffs);
 * mov dx,[0x531d38] (66 8b 15 = 16-bit moffs, _desiredMapScale+0xc);
 * add dx,ax; mov [esi],dx; a1 [wcZ]; sub eax,[ecx+8] (2b 41 08);
 * mov cx,[0x531d3a] (66 8b 0d, +0xe); cdq; idiv; add cx,ax; mov [esi+2],cx;
 * pop esi; ret. No remainder used: result word = 16-bit global + quotient. */
extern long wcX;        /* -> ?worldCenter@@3UF24_POINT3@@A */
extern long wcZ;        /* -> ?worldCenter@@3UF24_POINT3@@A+0x8 */
extern long mapScale;   /* -> ?mapScale@@3JA */
extern short panX;      /* -> _desiredMapScale+0xc */
extern short panY;      /* -> _desiredMapScale+0xe */

void __fastcall w32cMapWTSF2(long *wp, short *sp)
{
    long d;
    long q;
    short pan;
    short *s;

    d = wp[0];
    s = sp;
    d = d - wcX;
    q = d / mapScale;
    pan = panX;
    pan = pan + (short)q;
    s[0] = pan;
    d = wcZ;
    d = d - wp[2];
    q = d / mapScale;
    pan = panY;
    pan = pan + (short)q;
    s[1] = pan;
}