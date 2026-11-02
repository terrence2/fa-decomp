// ?PushShellAlloc@@YGXXZ @ rva 0xd360 (54112, 48 B) — stdcall void(void):
//   mov ax,[ctr16] / mov dl,[mmAllocId] / mov byte [mmAllocId],6 /
//   movsx ecx,ax / inc ax / mov [ctr16],ax / mov [ecx+shellArr],dl / ret.
extern short w27c_ctr;              /* =?remapDarken320@@3PAEA+0x14 */
extern unsigned char w27c_mmId;     /* =?mmAllocId@@3EA */
extern unsigned char w27c_shellArr[]; /* =_shellEvent+0x8 */

void __stdcall w27c_PushShellAlloc(void)
{
    short i = w27c_ctr;
    unsigned char b = w27c_mmId;
    w27c_mmId = 6;
    w27c_shellArr[i] = b;
    w27c_ctr = (short)(i + 1);
}
