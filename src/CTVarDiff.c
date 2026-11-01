// _CTVarDiff @ rva 0x63fa0 (64 B) — time a callback twice, return the signed
// short delta. FA asm:
//   push esi / push edi / mov esi,[esp+0xc] (fn) / call esi / mov di,ax
//   (r1 truncated straight into di, no movzx — fn is a cdecl int fn with a
//   (short) cast into a short local)
//   mov ax,ds:0x5423e8 (66 a1 moffs load of *(ushort*)(serviceTicks+0x20)) /
//   test ax,ax / je path2
//   push eax (raw reg push, stale uppers kept) / call PushCurObj@4 / call esi /
//   mov si,ax (r2 into si) / call PopCurObj@0 / shared tail:
//   movsx eax,di / movsx ecx,si / sub eax,ecx / pop edi / pop esi / ret
//   path2: movsx eax,di / mov si,di / pop edi / movsx ecx,si / sub / pop esi / ret
// Key C findings (probes b18c_CTVarDiff/2/3): the r2 = r1 duplication only
// survives CL's CSE when it is the else-branch feeding a SHARED
// return-(r1-r2) tail (separate-statement forms fold to xor eax,eax);
// w must be an unsigned short LOCAL (memory-read test gives 66 83 3d cmp);
// and PushCurObj's param must be declared unsigned short so CL pushes the
// raw eax without the and eax,0xffff widen — FA pushes eax with stale uppers
// exactly. Probe b18c_CTVarDiff3 byte-exact.
extern char serviceTicks[];
extern void __stdcall PushCurObj(unsigned short arg);
extern void __stdcall PopCurObj(void);
typedef int (*cvtfn_t)(void);

int __cdecl CTVarDiff(cvtfn_t fn)
{
    short r1, r2;
    unsigned short w;
    r1 = (short)fn();
    w = *(unsigned short *)(serviceTicks + 0x20);
    if (w) {
        PushCurObj(w);
        r2 = (short)fn();
        PopCurObj();
    } else
        r2 = r1;
    return (int)r1 - (int)r2;
}
