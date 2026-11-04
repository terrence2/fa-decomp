/* v3: child walk without the temp (c = c->f3c after the free, walker in
 * edi like FA); unlink else-branch: empty walk while, store guarded by
 * (t == p) so CL reuses the loop's cmp fall-through (no re-test). */
extern void __fastcall MMFreePtr(void *p);
extern void *w36g_dhead;   /* _serviceTicks+0x1c */

void dlg_list_shutdown(void *p)
{
    void *c = *(void **)p;
    if (c) {
        do {
            MMFreePtr(c);
            c = *(void **)((char *)c + 0x3c);
        } while (c != 0);
    }
    if (w36g_dhead == p) {
        w36g_dhead = *(void **)((char *)p + 0x20);
        MMFreePtr(p);
    } else {
        void *cur = w36g_dhead;
        void *t = *(void **)((char *)cur + 0x20);
        while (t != 0 && t != p)
            ;
        if (t == p)
            *(void **)((char *)cur + 0x20)
                = *(void **)((char *)p + 0x20);
        MMFreePtr(p);
    }
}