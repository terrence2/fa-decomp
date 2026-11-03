/* w34A @ rva 0xa3c90 (dec 670864), 48 B, FPO fpo/esp, unnamed ($FA$_t_4a3c90).
 * FA bytes: push esi/push edi/edi=edx/esi=ecx/call @RMFind@4(ecx=esi)/
 * push edi; mov ecx,esi; push eax; call @RMType@4(ecx=esi)/
 * push eax; push 0x505f44 (?fixupShape@@3DA+0x34); push 0; call _SMCallByName
 * (cdecl 5 args, add esp,0x14)/pop edi/pop esi/ret + 2-B + 7-B census pad.
 * fastcall(a,b): r=RMFind(a); SMCallByName(0, &fixupShape+0x34, RMType(a),
 * r, b).
 */
extern char w34_fix;        /* ?fixupShape@@3DA  */
extern int __fastcall RMFind(int);
extern int __fastcall RMType(int);
extern int __cdecl SMCallByName(int a, int b, int c, int d, int e);

int __fastcall w34_a3c90(int a, int b)
{
    int r = RMFind(a);
    return SMCallByName(0, (int)((char *)&w34_fix + 0x34),
                        RMType(a), r, b);
}