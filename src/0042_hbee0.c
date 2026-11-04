/* wave-41A probe v2a: 0x40bee0 — args corrected: RMAccessHandle(pal, 0x8104)
 * (FA pushes 0x8104 first = arg2, right-to-left). Arms as arrays so CL emits
 * b8 imm reloc loads, not a1 content loads. */
extern unsigned short w41a_mres;      /* ?menuResolution@@3FA = 0x4e8220 */
extern unsigned char w41a_palLo[];    /* ?remapDarken320@@3PAEA+0xf8 = 0x4e83c8 */
extern unsigned char w41a_palHi[];    /* ?remapDarken320@@3PAEA+0x108 = 0x4e83d8 */
extern void *w41a_msel8;              /* ?menuSelecting@@3DA+0x8 = 0x4e81e4 */

void __stdcall SetupBitmapAccess(long, long, long);
unsigned char * __stdcall RMAccessHandle(unsigned char *, unsigned long);

void __cdecl w41a_bee0(void)
{
    SetupBitmapAccess(0, 0, 0);
    w41a_msel8 = (void *)RMAccessHandle(
        w41a_mres == 0x140 ? w41a_palHi : w41a_palLo, 0x8104u);
}