/* ?CN_SetFactoryDefaults@@YAXPAUCN_INFO@@@Z @ rva 0x7e590 (112 B) -- v2.
 * v1 was right except: struct sizeof must be 0xDDC (memset count 0x377, not
 * 0x378) and the strcpy is guarded by if (janesOnlineName[0]) -- FA emits
 * a0/84 c0/74 25 before the bf/strlen/movs expansion. pad2 now 0xcf0. */
#include <string.h>

typedef struct {
    unsigned long f0;
    unsigned char blob[0x5c];
    unsigned long f60;
    unsigned long f64;
    unsigned char pad[0x54];
    unsigned long fbc;
    unsigned char pad2[0xcf0];
    struct { char t[0x2c]; } tcp;   /* +0xdb0 */
} W37H_CN;                          /* sizeof = 0xDDC */

extern char w37h_jol[];     /* ?janesOnlineName@@3PADA (treated as array) */
extern void NetSetFactoryTCP(void* tcp);

void CN_SetFactoryDefaults(W37H_CN* c)
{
    memset(c, 0, sizeof(W37H_CN));
    c->f0 = 3;
    c->f64 = 0;
    c->fbc = 8;
    c->f60 = 10;
    NetSetFactoryTCP(&c->tcp);
    if (w37h_jol[0])
        strcpy((char*)c + 4, w37h_jol);
}