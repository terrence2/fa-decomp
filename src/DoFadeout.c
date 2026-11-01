// _DoFadeout@0 @ rva 0x9e710 — snapshot curPalette to fadePalette (inline rep
//   movsd from #include <string.h>, 0x300 bytes) then run the dialog fade
#include <string.h>
extern char curPalette[];
extern char fadePalette[];
extern void __stdcall DialogFadeout(void);
void __stdcall DoFadeout_q(void)
{
    memcpy(fadePalette, curPalette, 0x300);
    DialogFadeout();
}
