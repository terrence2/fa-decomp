/* w30f_ _G_TileShutDown @ rva 0x47093 (dec 290963), 50 B gap chunk (no FPO)
 * FA:
 *   55 8b ec 53 56 57          push ebp / mov ebp,esp / push ebx,esi,edi
 *   83 3d e4 0e 4f 00 00       cmp [bltBuffer],0
 *   0f 84 15 00 00 00          je 0x4470bb
 *   8b 0d e4 0e 4f 00          mov ecx,[bltBuffer]
 *   e8 rel32                   call @MMFreeHandle@4
 *   c7 05 e4 0e 4f 00 00 00 00 00  mov [bltBuffer],0
 *   e9 00 00 00 00             jmp 0x4470c0
 *   5f 5e 5b                   pop edi,esi,ebx
 *   c9                         leave
 *   c3                         ret
 */
void __fastcall MMFreeHandle(void* h);
extern void* bltBuffer;

void __G_TileShutDown_v1(void)
{
    if (bltBuffer) {
        MMFreeHandle(bltBuffer);
        bltBuffer = 0;
    }
}