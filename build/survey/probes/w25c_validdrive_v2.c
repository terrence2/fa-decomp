// __validdrive @ rva 0xd5420 = 873504, 76 B — v2: buf[0] assignment hoisted
// to the buf[1..3] template's position to stop CL's push-ebx/nop dance, and
// plain `int` local.
__declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char *root);
/* map __imp__GetDriveTypeA@4=__imp__GetDriveTypeA */

int __cdecl w25c_validdrive_q(unsigned int drive)
{
    char buf[4];
    unsigned int t;
    if (drive == 0)
        return 1;
    buf[0] = (char)drive + 0x40;
    buf[1] = ':';
    buf[2] = '\\';
    buf[3] = '\0';
    t = GetDriveTypeA(buf);
    if (t != 0 && t != 1)
        return 1;
    return 0;
}