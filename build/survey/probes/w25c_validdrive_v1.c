// __validdrive @ rva 0xd5420 = 872480, 76 B
// FA asm: mov eax,[esp+4] / sub esp,4 / test eax,eax / jne B / (mov eax,1;
// add esp,4; ret) / B: byte template ':' '\\' 0 stored at [esp+1..3], then
// add al,0x40 / mov [esp],al (buf[0]='A'+drive-1) / lea eax,[esp]; push;
// call [__imp__GetDriveTypeA] / test eax / je ret0 / cmp eax,1 / je ret0 /
// mov eax,1 (success path in the middle) / add esp,4 / ret; ret0: xor eax,
// eax / add esp,4 / ret.  Param is the drive NUMBER (buf[0]=+0x40 = 'A').
__declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char *root);
/* map __imp__GetDriveTypeA@4=__imp__GetDriveTypeA */

int __cdecl w25c_validdrive_q(unsigned int drive)
{
    char buf[4];
    unsigned int t;
    if (drive == 0)
        return 1;
    buf[1] = ':';
    buf[2] = '\\';
    buf[3] = '\0';
    buf[0] = (char)drive + 0x40;
    t = GetDriveTypeA(buf);
    if (t != 0 && t != 1)
        return 1;
    return 0;
}