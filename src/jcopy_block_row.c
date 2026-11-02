/* ?jcopy_block_row@@YAXPAY0EA@F0I@Z @ rva 0x74fb0 (dec 479152), size 0x20 —
 * EXACT, pure C, no patches, no relocs.
 *
 * C recipe: memcpy(dst, src, n * 128) inlines to rep movsd while keeping
 * FA's shl ecx,7 / shr ecx,2 spelling of the count (the *128 lands before
 * the >>2 as in FA). Signed short row params via plain C pointers.
 *
 * fitobj: python3 tools/fitobj.py build/survey/probes/w24a_jcopy_block_row_v1.obj 479152 \
 *   build/survey/probes/w24a_jcopy_block_row_v1_fit.obj
 */
extern void *memcpy(void *, const void *, unsigned);
void jcopy_block_row(short *src, short *dst, unsigned n)
{
    memcpy(dst, src, n * 128);
}
