// ?SER_SendBytes@@YAXPAEJ@Z @ rva 0xa9040 (80 B)
// FA: push esi/a0 [Ctrl+0x12d]/test/je epilogue/esi=[esp+0xc](n)/
//   a1 eax=[Ctrl+0x22]/sub eax,esi/push esi(n)/mov ecx,[esp+0xc](buf)/
//   a3 [Ctrl+0x22],eax/push ecx(buf)/a1 eax=[Ctrl+0x26]/add eax,0x568112(&Ctrl+0x2a)/
//   push eax/call _memmove/add esp,0xc/8b 0d ecx=[Ctrl+0x26]/add ecx,esi/89 0d [Ctrl+0x26],ecx/
//   pop esi/ret
#include <string.h>
extern unsigned char serGate2d;     /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x12d */
extern unsigned long serQDepth;     /* +0x22 (previously mapped field name) */
extern unsigned long serWr;         /* +0x26 */
extern char serTx[];                /* +0x2a (buffer base for dst calc) */

void w42D_sersend(unsigned char *buf, long n)
{
    long v;
    long d;

    if (serGate2d == 0)
        return;
    v = serQDepth - n;
    d = serWr + (long)serTx;
    memmove((void *)d, buf, n);
    serQDepth = v;
    serWr = serWr + n;
}