// ?PopShellAlloc@@YGXXZ @ rva 0xd390 (32 B) — pop the next shell-alloc id.
// FA: ax=[idx] (66 a1); dec ax; movsx ecx,ax; [idx]=ax (66 a3);
// al=[ecx+_shellEvent+0x8]; [mmAllocId]=al (a2); ret.
extern unsigned short darkenIdx;   /* ?remapDarken320@@3PAEA+0x14 */
extern char shellTab[];            /* _shellEvent+0x8 */
extern unsigned char mmAllocId;

void __stdcall PopShellAlloc(void)
{
    darkenIdx = darkenIdx - 1;
    mmAllocId = shellTab[(short)darkenIdx];
}
