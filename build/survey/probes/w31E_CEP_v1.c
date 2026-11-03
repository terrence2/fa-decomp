// _CallEventProc@8 @ rva 0x62b80 = 404352, 96 B.
//   FA: sub esp,4; mov ecx,[_eventFilterProc]; test ecx,ecx; 90; push ebx;
//   je skip; lea eax,[esp+7](&ev[3]); lea edx,[esp+0x10](&p2); lea ebx,
//   [esp+0xc](&p1); push eax; push edx; push ebx; call ecx; add esp,0xc;
//   test al,al; je skip2; mov al,[esp+7]; pop ebx; add esp,4; ret 8;
//   skip: mov eax,[esp+0x10](p2); push eax; mov eax,[esp+0x10](p1);
//   and eax,0xffff; push eax; push 3; call _CallUtilProc; add esp,0xc;
//   pop ebx; add esp,4; ret 8.
extern unsigned char (__cdecl *eventFilterProc)(
    unsigned long *, unsigned long *, unsigned char *);
extern unsigned char __cdecl CallUtilProc(int, unsigned int, unsigned long);

unsigned char __stdcall CallEventProcQ(unsigned long *p1, unsigned long *p2)
{
    unsigned char ev[4];
    if (eventFilterProc != 0 && (*eventFilterProc)(p1, p2, ev + 3))
        return ev[3];
    return CallUtilProc(3, *p1 & 0xffff, *p2);
}