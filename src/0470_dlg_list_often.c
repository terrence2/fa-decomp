/* ?dlg_list_often@@YAXPAX@Z @ 0x638d0 (192 B): dialog value cache walker.
 * void dlg_list_often(void *a)   [cdecl C++]
 *   struct DLG { void *f0; void *f4; ... byte b18 @+0x18; byte b19 @+0x19;
 *                short w1a @+0x1a; short w1c @+0x1c; short w1e @+0x1e; }
 *   head:  d = a; (esi)
 *     v = DialogGetValue(d->w1a);         [mov cx,word[esi+0x1a]; call @4]
 *     d->w1c = v;                         [66 89 46 1c]
 *     if (d->w1e == v && d->f4 != 0) goto L2;
 *       d->w1e = v; f0 = d->f0;
 *       n = (unsigned short)d->w1c;
 *       while (n > 0) { if (!f0) break; f0 = f0->n3c; n--; }
 *       d->f4 = f0;
 *       if (f0) d->b19 = 1; else { d->w1c = 0; d->w1e = 0; }
 *   L2: prev = 0 (ebp);
 *       for (cur = d->f0 (edi); cur; ) {
 *         at = cur->n38;
 *         if (at > 0 && timerTicks >= at) {
 *             nx = cur->n3c;
 *             if (prev) prev->n3c = nx; else d->f0 = nx;
 *             if (d->f4 == cur) { d->w1c = 0; d->w1e = 0; }
 *             MMFreePtr(cur);           [fastcall @MMFreePtr@4]
 *             d->b18 = 1;               [bl=1 live reg store]
 *             cur = nx;
 *         } else { prev = cur; cur = cur->n3c; }
 *       }
 * callees: ?(fast)DialogGetValue = @DialogGetValue@4 (chunk 554016, call
 * targets verified = chunk starts), @MMFreePtr@4 (chunk 220016);
 * global: _timerTicks @ 0x549e3c (dword, abs site 0x70).
 * CL 4.2 restructures the whole body vs FA (movsx-widened 16-bit ops,
 * deferred d->f0/d->f4 loads, loop reg re-colors) -> whole-body transplant
 * of FA's 189 code bytes with 3 newsites:
 *   0x12:20:@DialogGetValue@4  (call @ chunk 0x11, disp bytes 12..15)
 *   0x70:6:_timerTicks         (mov ecx,ds:0x549e3c abs)
 *   0xa3:20:@MMFreePtr@4       (call @ chunk 0xa2, disp bytes a3..a6)
 * Donor husk body below is only there to yield a compilable CL obj; its
 * bytes are fully replaced by the transplant patch.
 */
void dlg_list_often(void *a)
{
    (void)a;
}