// __validdrive v3: char-typed drive param (val is read as a byte: FA's
// add al,0x40 on the parked eax) and volatile buf to keep the explicit
// byte stores in FA's order (template first, then the +0x40 byte).
__declspec(dllimport) unsigned int __stdcall GetDriveTypeA(const char *root);
/* map __imp__GetDriveTypeA@4=__imp__GetDriveTypeA */

int __cdecl w25c_validdrive_q(char drive)
{
    char buf[4];
    unsigned int t;
    if (drive == 0)
        return 1;
    buf[1] = ':';
    buf[2] = '\\';
    buf[3] = '\0';
    buf[0] = drive + 0x40;
    t = GetDriveTypeA(buf);
    if (t != 0 && t != 1)
        return 1;
    return 0;
}