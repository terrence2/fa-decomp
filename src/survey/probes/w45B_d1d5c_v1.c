/* do_new_pmap_or_tmap @ rva 0xd1d5c (128 B, tail pad cc 1 B) -- interp
 * do-handler, sibling of do_collision_info (w45B_d0608 transplant recipe).
 * esi = interp data cursor (three signed uword deltas at [esi], [esi+2],
 * [esi+4]); reads viewer_x/y/z+2 word slots (0x113bd0/bd4/bd8), abs-diffs
 * the x/y deltas (neg on sign), sorts into 16-bit max via cmp/xchg, takes
 * (max>>2 of two terms) sum, compares against [esi+4] distance, then posts
 * new interp cmd 0xde (< dist) or 0xdc (>= dist) into [esi], reloads it,
 * esi += 2, movzx ebx,al and dispatches jmp [ebx*4 + vector_table]
 * (sib-5d; both cmd paths dispatch; the eb 17 after the first dispatch is
 * dead code FA keeps, and points at the cc census pad).
 * Whole-body transplant: husk documents semantics; FA bytes authoritative
 * (CL cannot emit ff 24 5d jump-table forms). */
long do_new_pmap_or_tmap(long cmd);

long do_new_pmap_or_tmap(long cmd)
{
    return 0;
}