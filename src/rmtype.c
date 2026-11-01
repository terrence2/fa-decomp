// @RMType@4 @ rva 0xa3700 (16 B)
// FA: push 0x2e / push ecx / call _strchr / add esp,8 / inc eax / ret
extern char *__cdecl strchr(const char *, int);

char *__fastcall RMType(const char *s)
{
    return strchr(s, 0x2e) + 1;
}
