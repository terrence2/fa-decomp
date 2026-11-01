// _DialogWhatItem@0 @ rva 0x870e0 (16 B) — mov eax,[dialogItemPtr] / ret
//   (FA's anchor is the C++-mangled ?dialogItemPtr@@3PAEA; --map retargets)
extern unsigned char *dialogItemPtr_x;

unsigned char *__stdcall DialogWhatItem(void)
{
    return dialogItemPtr_x;
}
