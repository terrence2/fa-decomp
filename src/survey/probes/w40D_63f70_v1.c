/* w40D_63f70: unnamed 48-B chunk @ 0x463f70 (rva 0x63f70)
 * a1 [svc46] / test cl / mov word [svc4e],1 / mov [svc4a],eax / je L
 * xor eax,eax / mov [svcA2],ax / mov [curFlag215],al / ret
 * maps: _svc46=_serviceTicks+0x46, _svc4e=_serviceTicks+0x4e,
 *       _svc4a=_serviceTicks+0x4a, _svcA2=_serviceTicks+0xa2,
 *       _curFlag=_curThing+0x215
 */
typedef unsigned long ulong;
typedef unsigned short ushort;

extern ulong        svc46;
extern ushort       svc4e;
extern ulong        svc4a;
extern ushort       svcA2;
extern unsigned char curFlag;

void __fastcall svcUpd(char flag)
{
    ulong t;
    ushort z;
    t = svc46;
    svc4e = 1;
    svc4a = t;
    if (flag) {
        z = 0;
        svcA2 = z;
        curFlag = (unsigned char)z;
    }
}