/* w38F_a2ff0_v2: ?socket_close_socket@@YAXIG@Z — ushort linger struct {1,0},
 * dllimport Sleep(200), ws-struct field fn-pointer calls (stdcall). */
extern "C" {
__declspec(dllimport) void __stdcall Sleep(unsigned long);
extern int (__stdcall *w38f_s32)(unsigned long, unsigned long, unsigned long, void *, unsigned long);
extern unsigned long (__stdcall *w38f_sh)(unsigned long);
}

void socket_close_socket(unsigned int s, unsigned short h)
{
    struct { unsigned short onoff, how; } lg;
    lg.onoff = 1;
    lg.how = 0;
    Sleep(200);
    w38f_s32(s, 0xffff, 0x80, &lg, 4);
    w38f_sh(s);
}