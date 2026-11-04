/* probe w39B: _overflow_handler_reg @ 0x4bb5f0 (112 B, FPO, 1 cdecl param)
 *
 * FA bytes live path:
 *   8b 4c 24 04        mov ecx,[esp+4]        ; xp
 *   8b 01 8b 00        mov eax,[ecx]; mov eax,[eax]   ; code = rec[0]
 *   3d 94 00 00 c0 / 74 0b      == 0xC0000094 -> L
 *   3d 95 00 00 c0 / 74 04      == 0xC0000095 -> L
 *   33 c0 5b c3        xor eax,eax; pop ebx; ret      ; return 0
 * L:
 *   8b 49 04           mov ecx,[ecx+4]        ; ctx
 *   83 81 b8 00 00 00 03   ctx[46] += 3       ; Eip += 3
 *   8b 91 b0..         mov edx,[ecx+0xb0]     ; Eax
 *   89 15 30 62 58 00  ovf[2] = Eax   (moffs _overflow_ptr+8)
 *   8b 99 a8..         mov ebx,[ecx+0xa8]     ; Edx
 *   89 1d 3c 62 58 00  ovf[5] = Edx   (moffs _overflow_ptr+0x14)
 *   [dead 16-bit block: 66 0b c0 66 b8 00 7e 75 08 66 0b d2 75 03 66 2b c0 66 33 d2]
 *   a1 30 62 58 00     mov eax,ovf[2]
 *   5b                 pop ebx
 *   89 81 b0..         ctx[44] = Eax
 *   b8 ff ff ff ff     mov eax,-1
 *   8b 15 3c 62 58 00  mov edx,ovf[5]
 *   89 91 a8..         ctx[42] = Edx
 *   c3                 ret
 *
 * The 20-B dead ax/dx block is FA codegen of an eliminated expression; we
 * patch-insert it. */
typedef unsigned long ulong;

struct XP { void *rec; void *ctx; };

extern ulong _overflow_ptr[];

ulong _overflow_handler_reg(struct XP *xp)
{
    ulong code = *(ulong *)*(void **)xp;
    if (code == 0xc0000094 || code == 0xc0000095) {
        ulong *ctx = (ulong *)xp->ctx;
        ulong a, d;
        ctx[46] += 3;
        a = ctx[44]; _overflow_ptr[2] = a;
        d = ctx[42]; _overflow_ptr[5] = d;
        ctx[44] = _overflow_ptr[2];
        ctx[42] = _overflow_ptr[5];
        return (ulong)-1;
    }
    return 0;
}