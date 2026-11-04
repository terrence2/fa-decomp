/* w35B: unnamed 0x83970 (64 B) — fastcall vector add: c[0..2,4,3]+=d[...]
 * FA: push ebx; eax=[edx]; push esi; ebx=[ecx]; push edi; ebx+=eax; push ebp;
 * esi=[ecx+4]; edi=[ecx+8]; [ecx]=ebx; esi+=[edx+4]; [ecx+4]=esi;
 * edi+=[edx+8]; eax=[ecx+0x10]; [ecx+8]=edi; ebx=[edx+0x10]; pop ebp;
 * eax+=ebx; pop edi; pop esi; [ecx+0x10]=eax; edx=[edx+0xc]; eax=[ecx+0xc];
 * eax+=edx; pop ebx; [ecx+0xc]=eax; ret (+7 B pad).
 * 0x10 block emitted BEFORE 0xc block -> source order c0,c1,c2,c4,c3.
 */
void __fastcall w35b_vadd(long *c, long *d)
{
    c[0] += d[0];
    c[1] += d[1];
    c[2] += d[2];
    c[4] += d[4];
    c[3] += d[3];
}