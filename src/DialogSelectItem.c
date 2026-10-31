/* DialogSelectItem — pilot 4 (chunk @ rva 0x87610, size 0x90).
 *
 * FA asm (chunk):
 *   push esi; mov si,cx; call PushShellAlloc; mov ecx,esi; call DialogGetPtr;
 *   mov esi,eax; mov ax,[esi]; and eax,0x7fff; dec eax; cmp eax,7;
 *   ja tail; xor ecx,ecx; mov cl,[idx_tab+eax]; jmp [jmp_tab+ecx*4]
 *   body1 (cases 1,5): mov ax,[esi+0x17]; push eax; call SUB_87070;
 *     add esp,4; mov [lastDial],eax; movb [esi+0x16],1; jmp tail
 *   case 3: movb [esi+0x16],1
 *   case 8: movb [esi+0x1e],1 ; fall through tail
 *   tail: mov al,[firstDraw]; test al,al; jne end; push esi; call DialogDraw;
 *     end: call PopShellAlloc; pop esi; ret
 *   jmp_tab @ 0x87678 (5 VAs, fixups), idx_tab @ 0x8768c (8 B),
 *   then 05 00 00 00 00 (?), lea-pad to 0x90.
 */
extern void __stdcall PushShellAlloc(void);
extern void* __fastcall DialogGetPtr(unsigned short idx);
extern void __stdcall DialogDraw(void* d);
extern void __stdcall PopShellAlloc(void);
extern int SUB87070(unsigned short v); /* cdecl — FA has caller-pops 83 c4 04 */
extern void* lastDial;
extern char firstDraw;

void __fastcall DialogSelectItem(unsigned short item)
{
    unsigned char* d;
    unsigned short sel;

    sel = (unsigned short)item;
    PushShellAlloc();
    d = (unsigned char*)DialogGetPtr(sel);
    switch (*(unsigned short*)d & 0x7fff) {
    case 1:
    case 5:
        lastDial = (void*)SUB87070(*(unsigned short*)&d[0x17]);
        d[0x16] = 1;
        break;
    case 3:
        d[0x16] = 1;
        break;
    case 8:
        d[0x1e] = 1;
        break;
    default:
        /* FA's ja (default) skips the firstDraw/DialogDraw check but rejoins
         * the SHARED PopShellAlloc epilogue */
        goto skip_draw;
    }
    if (!firstDraw)
        DialogDraw(d);
skip_draw:
    PopShellAlloc();
}