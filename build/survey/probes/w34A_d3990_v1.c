/* w34A @ rva 0xd3990 (dec 866704), 32 B, FPO fpo/esp, unnamed ($FA$_t_4d3990).
 * FA bytes: push esi/push edi/edi=[esp+0x10](hi)/esi=[esp+0xc](lo)/
 * cmp edi,esi; jbe epilog/do { eax=[esi]; test; je skip; call eax;
 * add esi,4 } while (edi>esi)/pop edi/pop esi/ret.
 * CRT _initterm spelling (cdecl, p1=lo, p2=hi).
 */
void __cdecl w34_d3990(long **lo, long **hi)
{
    if ((unsigned long)lo < (unsigned long)hi) {
        do {
            void *fn = *lo;
            if (fn != 0)
                ((void (__cdecl *)(void))fn)();
            ++lo;
        } while ((unsigned long)lo < (unsigned long)hi);
    }
}