/* dlg_list_clear - FA rva 0x63990 (407952) - EXACT probe verdict, tier1_a_r4.json entry 'Dlg_list_clear_v4'
 * Form: patch-hybrid
 * Levers: 3 patches: 2 modrm + 10-byte loop reorder with REL32 re-add
 * Maps: _MMFreePtr@4=@MMFreePtr@4
 * patch 0x7: -> 37
 * patch 0x9: -> f6
 * patch 0xc: 10 B 8b ce 8b 76 3c e8..., REL32 re-add @MMFreePtr@4 at site 6
 * Probes: v1-v4
 */
extern void __fastcall MMFreePtr(void *p);

void dlg_list_clear(void *head)
{
    void **h = head;
    void *n = h[0];
    if (n) {
        do {
            void *t = *(void **)((char *)n + 0x3c);
            MMFreePtr(n);
            n = t;
        } while (n);
    }
    h[0] = 0;
    h[1] = 0;
    *(unsigned short *)((char *)h + 0x1c) = 0;
    *(unsigned short *)((char *)h + 0x1e) = 0;
    *(char *)((char *)h + 0x18) = 1;
}
