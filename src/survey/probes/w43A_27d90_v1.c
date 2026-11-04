/* rva 0x27d90 (96 B) - object pick test (fastcall e in ecx)
 * FA: push esi; eax=ecx; and eax,0xffff; edx=1; esi=*[eax*4+_objPtrs];
 * call check(e,1) [ecx=e untouched, edx=1]; test al; je; mov al,1 ret;
 * eax=[esi+1]; test al,0x10; je; ret 1;
 * eax=[esi+5] (q); cl=[eax]; cmp cl,3 je / cmp cl,5 jne;
 * [q+0xb3] word: if !=0 return 0; cmp [si+0x74],0; setne al; ret.
 */
extern void *objPtrsQ[];
extern unsigned char __fastcall w43aCheck3(unsigned long, long);

unsigned char __fastcall w43A_27d90(unsigned long e)
{
    void *t;
    long q;
    unsigned char c;
    t = objPtrsQ[e & 0xffff];
    if (w43aCheck3(e, 1)) return 1;
    if (*(long *)((char *)t + 1) & 0x10) return 1;
    q = *(long *)((char *)t + 5);
    c = *(unsigned char *)q;
    if (c == 3 || c == 5) {
        if (*(short *)((char *)q + 0xb3) != 0) return 0;
    }
    return *(short *)((char *)t + 0x74) != 0;
}