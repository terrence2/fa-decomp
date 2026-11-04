/* _SaveFile @ 0xaa1a0 (149 B code + census pads): save-file helper.
 * char SaveFile(char *name, void *buf, long len):
 *   dosError = 0;                       [33 f6; 66 89 35 word store via si=0]
 *   h = Create(name);                   [fastcall @Create@4 -> ax]
 *   if (h == -1) { dosError = 0; return 0; }   [66 3d ff ff; 66 8b d8]
 *   if (Write(h, buf, len) != len) {    [_Write@12 stdcall; cmp eax,esi;
 *     Close(h);                         [fastcall @Close@4, ecx=ebx]
 *     Delete(name);                     [fastcall @Delete@4, ecx=edi]
 *     dosError = 0; return 0; }
 *   Close(h); dosError = 0;
 *   if (LibUpdate(name))                [cdecl; test eax,eax; je skip]
 *     ErrorExit(tcp_proto + 0xf0);      [push 0x507e38 DIR32 (EMPTY bytes),
 *                                        tcp_proto = 0x507d48, +0x2f0? =
 *                                        0x507d48+0xf0 = 0x507e38]
 *   NamesShutdown();                    [_NamesShutdown@0 stdcall]
 *   return 1.
 * dosError stores are 16-bit: entry store sources si (66 89 35), later
 * stores imm (66 c7 05). bx=ax handle save (66 8b d8).
 */
extern short dosError;
extern short __fastcall w45E_Create(char *name);
extern long __stdcall Write(long h, void *buf, long len);
extern void __fastcall w45E_Close(long h);
extern void __fastcall w45E_Delete(char *name);
extern int LibUpdate(char *name);
extern void ErrorExit(char *msg);
extern void __stdcall NamesShutdown(void);
extern char tcp_proto[];

char SaveFile(char *name, void *buf, long len)
{
    short h;
    long w;

    dosError = 0;
    h = w45E_Create(name);
    if (h == -1) {
        dosError = 0;
        return 0;
    }
    w = Write(h, buf, len);
    if (w != len) {
        w45E_Close(h);
        w45E_Delete(name);
        dosError = 0;
        return 0;
    }
    w45E_Close(h);
    dosError = 0;
    if (LibUpdate(name))
        ErrorExit(tcp_proto + 0xf0);
    NamesShutdown();
    return 1;
}