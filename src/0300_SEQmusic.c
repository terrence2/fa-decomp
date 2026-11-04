/* _SEQmusic (112 B) - cdecl (char *s, int f): buf[16] on the frame,
   strcpy(buf,s) + strcat(buf,valkyriesScore+0x7d4) inline expansions
   (scasb strlen + rep movsd/movsb pairs), then MusicOn(buf, f) fastcall
   (buf in ecx, f loaded dword into edx). */
#include <string.h>
extern char w43c_valk[];     /* ?valkyriesScore@@3DA+0x7d4 */
extern void __fastcall w43c_musonq(char *s, int f);  /* ?MusicOn@@YIXPADF@Z */
void __cdecl w43c_sqmusicq(char *s, int f)
{
    char buf[16];
    strcpy(buf, s);
    strcat(buf, w43c_valk);
    w43c_musonq(buf, f);
}
