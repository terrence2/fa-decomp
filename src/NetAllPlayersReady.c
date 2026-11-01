// ?net_all_players_ready@@YADXZ @ rva 0xadfb0 (32 B) — FA asm: a1
//   <?player_list@@3UNET_PLAYER_LIST@@A>+0/8b 0d <+0x8>/3b c8/0f 94 c0
//   (sete al)/c3.  Naked-asm escape, twin of SER_RemoteQueueFull: FA streams
//   the a1/eax-load first and compares ecx,eax; CL 4.2 always streams the
//   ecx-load first (v1/v2 C forms both stream mov ecx first, cmp ecx,eax).
//   Probe build/w4probe/w19_aprready_v5.obj — exact.
extern long netPlBaseG;   /* ?player_list@@3UNET_PLAYER_LIST@@A */
extern long netPlCntG;    /* ?player_list@@3UNET_PLAYER_LIST@@A+0x8 */

__declspec(naked) char netAPR_f(void)
{
    __asm {
        mov eax, netPlBaseG
        mov ecx, netPlCntG
        cmp ecx, eax
        sete al
        ret
    }
}