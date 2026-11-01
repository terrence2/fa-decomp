// @DialogDeselectItem@4 @ rva 0x876a0 (80 B) — FA asm (plain-C reachable):
//   push shell alloc / d = DialogGetPtr(item) / switch (*(ushort*)d&0x7fff):
//   case 3 -> d[0x16]=0; case 8 -> d[0x1e]=0; default -> pop+return /
//   if !firstDraw DialogDraw(d) / pop shell alloc.
// Clears the item's selected flag for its dialog type. Plain C matched
// CL's reg plan after the switch rewrite (probe b19b_deselect_v1 exact).
// Maps: DialogDraw/PushShellAlloc/PopShellAlloc are C++-mangled FA
// functions (?f@@YG..Z), so map FROMs carry the C stdcall decoration and
// TOs the mangled spellings; DialogGetPtr/firstDraw resolve identity.
extern void __stdcall PushShellAlloc(void);
extern void* __fastcall DialogGetPtr(unsigned short idx);
extern void __stdcall DialogDraw(void* d);
extern void __stdcall PopShellAlloc(void);
extern char firstDraw;

void __fastcall DialogDeselectItem(unsigned short item)
{
    unsigned char* d;

    PushShellAlloc();
    d = (unsigned char*)DialogGetPtr(item);
    switch (*(unsigned short*)d & 0x7fff) {
    case 3:
        d[0x16] = 0;
        break;
    case 8:
        d[0x1e] = 0;
        break;
    default:
        PopShellAlloc();
        return;
    }
    if (!firstDraw)
        DialogDraw(d);
    PopShellAlloc();
}