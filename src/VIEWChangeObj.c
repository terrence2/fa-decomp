// _VIEWChangeObj@12 @ rva 0xf310 (64 B) — 3-param stdcall.
// FA: mov ax,[esp+8](v) FIRST, mov ecx,[esp+4](obj); test byte[ecx+0x1a],1;
//   if set: cmp word[ecx+0x1c],ax; jne shared-ret12; mov eax,[esp+0xc]
//     (ushort arg home, stale uppers — fastcall stack arg); xor edx,edx;
//     push eax; call $FA$_t_40e1e0 @VCObjCalleeQ@12 (fastcall: ecx=obj —
//     the callee saves ecx and rep-movs 0x30 dwords from [ecx]; edx=flag
//     input; ret 4 cleans the stack arg); ret 0xc (own ret);
//   else: cmp word[ecx+0x1c],ax; jne shared-ret12; mov ax,[esp+0xc]
//     (16-bit view for the store); mov word[ecx+0x1c],ax; shared ret 12.
// v is pre-materialized in ax at entry (id-first load order); arg is
// ushort: full-dword home push for the call, 16-bit reload for the store.
struct VObj {
    unsigned char pad[0x1a];
    unsigned char flag;
    unsigned short w;
};

extern void __fastcall VCObjCalleeQ(struct VObj *obj, int flag, unsigned short arg);
                                     /* @VCObjCalleeQ@12 -> $FA$_t_40e1e0 */

void __stdcall VIEWChangeObj(struct VObj *obj, short v, unsigned short arg)
{
    unsigned short id = (unsigned short)v;

    if (obj->flag & 1) {
        if (obj->w == id) {
            VCObjCalleeQ(obj, 0, arg);
            return;
        }
    } else {
        if (obj->w == id)
            obj->w = arg;
    }
}
