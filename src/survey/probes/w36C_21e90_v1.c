/* w36C 0x21e90 (unnamed, 48 B) v1: plain C.  FA: 66 a1=_curScreen (word
 * moffs); 66 3d 0c/03 imm16 cmps; je store / jne ret; dword store
 * special_c8=0; byte store dms_1c=1; ret; 12-B pad.  Merged || arm. */
extern short curScreen;             /* identity _curScreen */
extern unsigned long specialsC8X;   /* _specialsC8X=_specials+0xc8 */
extern unsigned char desiredMapScale1cX; /* _desiredMapScale1cX=_desiredMapScale+0x1c */

void f_21e90(void)
{
    if (curScreen == 12 || curScreen == 3) {
        specialsC8X = 0;
        desiredMapScale1cX = 1;
    }
}