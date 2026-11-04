/* unnamed @ rva 0x2850e (77 B) — WP pos extractor, thiscall-ish edi=ecx out.
 * if (*(short*)(_desiredMapScale+4)): idx = (u16)*(short*)(dms+4);
 *   esi = _objPtrs[idx] + 0x11; copy 3 dwords; return.
 * elif (cmp *(int*)(dms+0x18) == 0): WPPos(idx=*(int*)(dms+0x18), this);
 *   return (jmp past the copy);
 * else: esi = _specials[*(int*)(worldCenter+0x10)] + 2; copy 3 dwords.
 * Transplant entry — verbatim FA body (movzx u16 dispatch, objPtrs/specials
 * table walks; CL diverges on the u->w type and cmp forms). */
extern char desiredMapScale;
extern void **objPtrs;
extern int worldCenter;
extern void **specials;
extern long __stdcall WPPosX(int a, void *b);

void w44h_2850e(int *this)
{
    this[0] = (int)&desiredMapScale + (int)objPtrs + worldCenter + (int)specials;
    (void)WPPosX(0, (void *)this);
}
