/* Transplant husk (whole-body patch) for do_set_gouraud, rva 853780 (0xd0714), 104 B.
 * FA semantics (dis.py 0xd0714): cdecl cdecl interpreter-op dispatcher, esi = op stream:
 *   op = (short)*esi++; esi += 2;                     // 66 8b 06 / 8d 76 02 / movsx
 *   do_collision_info(eb = (ebx=1, call); ...)        // ebx=1 then call do_collision_info+0x14
 *   if ((long)_effects & 1) { gouraudOn = 1;
 *       ppolygon = @G_SPolygonFlip@8; *(ppolygon+4) = @G_SUPolygonFlip@8; }
 *   else { gouraudOn = 0;
 *       ppolygon = @G_PolygonFlip@8; *(ppolygon+4) = @G_UPolygonFlip@8; }
 *   next op: bx = (unsigned char)op; jmp [ebx*2+vector_table]  // ff 24 5d [vector_table]
 * The bare public `do_set_gouraud` is not CL-C spellable; the husk only provides the
 * compiled donor (fitobj re-names the section symbol to the bare public per the $FA$_t
 * precedent). Body fully patched over husk.
 */
void do_set_gouraud(long a) { (void)a; }