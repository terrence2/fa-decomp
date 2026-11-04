// chunk @ rva 0xdf2c0 (5 B, unnamed) — e9 rel32 tail-jmp thunk to the
// neighbor chunk parked at $FA$_t_4df2d0. FPO record covers cbProcSize=5.
// Neighbors reference this chunk's gap anchor, the object must define
// $FA$_t_4df2c0 (wave-21 alias rule, --alias 0=$FA$_t_4df2c0).
extern void df2c0T(void);            /* $FA$_t_4df2d0 */

void __declspec(naked) Chunk_df2c0_q(void)
{
    __asm { jmp df2c0T }
}