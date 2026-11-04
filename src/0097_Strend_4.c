// @Strend@4 @ rva 0x11ee0 — push edi / mov edx,ecx / repne scasb (strlen
//   inline) / lea eax,[ecx+edx-1] / pop edi / ret (probe w4probe/v2).
char * __fastcall Strend(char *s)
{
    return s + strlen(s);
}
