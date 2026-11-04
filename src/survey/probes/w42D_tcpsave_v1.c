// ?tcp_save_settings@@YAXPAUNET_PROTOCOL@@PAUCN_INFO@@@Z @ rva 0xa8c20 (96 B)
// FA: mov ecx,[esp+8] (arg2=cn)/push ebx/push esi/add ecx,0xdb0/mov edx,tcp_settings/
//   3dword copy (ea/eb/ecx reuse, base-cached in edx: 89 02/89 5a 04/89 4a 08)/
//   cmp word [tcp+8],0 (66 83 3d)/jne/mov word [tcp+8],0x6ff (66 c7 05)/
//   a0 mov al,[tcp+0xa]/test/jne epilogue/mov eax,[esp+0xc] (arg1=proto)/
//   esi=[eax+0x14]/push esi/call f(esi)/add esp,4/push eax/push esi/call g(esi,eax)/
//   add esp,8/a3 [tcp],eax/pop esi/pop ebx/ret
extern unsigned long tcpSv0;        /* ?tcp_settings@@3UCN_INFO_TCP@@A +0 */
extern unsigned long tcpSv1;        /* +4 */
extern unsigned long tcpSv2;        /* +8 */
extern unsigned short tcpSvW;       /* +8 (low word) */
extern unsigned char tcpSvB;        /* +0xa */
extern unsigned long __cdecl w42D_tcpF(unsigned long v);   /* $FA$_t_4a8fe0 */
extern unsigned long __cdecl w42D_tcpG(long a, long b);    /* $FA$_t_4a9030 */

void w42D_tcpSave(void *proto, void *cn)
{
    long *s;
    long *d;
    long v;

    s = (long *)((char *)cn + 0xdb0);
    d = &tcpSv0;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    if (tcpSvW == 0)
        tcpSvW = 0x6ff;
    if (tcpSvB == 0) {
        v = *(long *)((char *)proto + 0x14);
        tcpSv0 = (unsigned long)w42D_tcpG(v, (long)w42D_tcpF((unsigned long)v));
    }
}