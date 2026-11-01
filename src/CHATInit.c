// _CHATInit@0 @ rva 0x12eb0 — chatEditing = 0 then three init calls, tail-jmp
//   to the unnamed init helper at 0x12ed0 (gap anchor $FA$_t_412ed0).
extern char chatEditing;
extern void __stdcall HUDInitMessages(void);
extern void __stdcall MSGInit(void);
extern void __stdcall MPShellInitMessages(void);
extern void t12ed0(void);

void CHATInit_q(void)
{
    chatEditing = 0;
    HUDInitMessages();
    MSGInit();
    MPShellInitMessages();
    t12ed0();
}
