// ?SeqGRFind@@YAPAUSEQGR@@PAD@Z @ rva 0x45c30 (74 B; census tail 6 B) —
// circular-list name search from global seqGraphics: inline strcmp
// (2 B/iter, sbb/sbb tail), advance p = p->next (off 0x2c), return 0 on
// wrap. FA: 53 / a1 seqGraphics / 56 / 8b 74 24 0c / inline strcmp /
// 85 c9 74 / 8b 40 2c / 8b 0d seqGraphics / 3b c8 75 / 33 c0 / 5e 5b c3
#include <string.h>
typedef struct SEQGR {
    char name[0x2c];
    struct SEQGR *next;
} SEQGR;
extern SEQGR *seqGraphics;

SEQGR *__cdecl SeqGRFind(char *name)
{
    SEQGR *p = seqGraphics;
    while (strcmp(name, p->name))
    {
        p = p->next;
        if (p == seqGraphics)
            return 0;
    }
    return p;
}