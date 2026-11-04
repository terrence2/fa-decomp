/* ?MOD_InitPortAndModem@@YAJPAUCN_INFO@@J@Z (rva 0x98800, 128 B, cdecl,
 * returns long, (CN_INFO *info, long mode)): modem bring-up ladder.
 *   1. ?SER_Initialize1 (rva 0x4bb90): must return 2, else 0 (no release).
 *   2. ?SER_Initialize2 (rva 0x4bbf0): must return 2, else release via
 *      _UnInitializePort@4 and 0.
 *   3. _ModemAttention@4 with *?Ctrl+0x234: truthy -> release and 0.
 *   4. _SetPortCharacteristics@24 with (ctrl, *(long*)((char*)info+0x60),
 *      0, 3, 0, 0) - six full-dword stdcall args, FA pushes them in
 *      interleave order (6a 00 / mov eax,[edi+0x60] / 6a 00 / mov ecx,[..]
 *      / 6a 03 / 6a 00 / push eax / push ecx).
 *   5. _ModemInit@4: truthy -> release and 0; success returns 2.
 * The ?Ctrl+0x234 reads are a1/8b 0d moffs DIR32 sites; the three failure
 * paths share one release exit (jne-short merges at 0x67), which CL spells
 * as a short-circuit || chain - same semantics, different bytes.
 */
extern long __stdcall SER_Initialize1(void *info, long mode);
extern long __stdcall SER_Initialize2(void *info, long mode);
extern long __stdcall ModemAttention(void *ctrl);
extern long __stdcall SetPortCharacteristics(void *ctrl, long cfg,
                                             long b1, long b2, long b3, long b4);
extern long __stdcall ModemInit(void *ctrl);
extern long __stdcall UnInitializePort(void *ctrl);
extern void *w44e_ctrl234;      /* ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x234 */

long __cdecl w44e_MODInitPortAndModem(void *info, long mode)
{
    void *ctrl = w44e_ctrl234;
    if (SER_Initialize1(info, mode) != 2)
        return 0;
    if (SER_Initialize2(info, mode) != 2 || ModemAttention(ctrl)
        || (SetPortCharacteristics(ctrl, *(long *)((char *)info + 0x60),
                                  0, 3, 0, 0), ModemInit(ctrl)))
        return UnInitializePort(ctrl), 0;
    return 2;
}