// _ScreenDirty@0 @ rva 0x9e630 (48 B) — signed word count at _grMode+0xc
//   (cmp-word / push edi / jle out), then CL 4.2's variable-length inline
//   memset: mov edi,_lineStats / mov eax,-1 / movsx edx,word / shr 2 /
//   rep stosd / and 3 / rep stosb.  Both reads hit the memory operand.
#include <string.h>
extern char grMode[];
extern char lineStats[];
void ScreenDirty_q(void)
{
    if (*(short *)(grMode + 0xc) > 0)
        memset(lineStats, 0xff, *(short *)(grMode + 0xc));
}