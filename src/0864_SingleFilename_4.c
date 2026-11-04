// _SingleFilename@4 @ rva 0x9f070 (48 B) — inline strcpy(singleFilenameBuf
// @ ?stereoSeparation@@3GA+0x8, param): push esi/mov ecx,-1/push edi/sub
// eax,eax/edi=[esp+0xc] src/scasb/not ecx/sub edi,ecx/eax=len/shr ecx,2/
// esi=src/edi=buf/rep movsd/mov ecx,eax/and ecx,3/rep movsb/pop edi/esi/ret 4.
// Plain C strcpy with <string.h> intrinsic (probe w13b_SingleFilename).
#include <string.h>

extern char singleFilenameBuf_[];

void __stdcall SingleFilename(char *s)
{
    strcpy(singleFilenameBuf_, s);
}