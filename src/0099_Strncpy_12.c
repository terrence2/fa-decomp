// _Strncpy@12 @ rva 0x11f60 (48 B) — FA asm: mov eax,[esp+8] (src) / push
//   esi / mov esi,[esp+8] (dst) / push edi / mov edi,[esp+0x14] (n) / push
//   edi/eax/esi / call _strncpy (cdecl) / add esp,0xc / mov byte
//   [esi+edi*1],0 / pop edi/esi / ret 0xc.  Plain C __stdcall wrapper:
//   strncpy(3) then dst[n]=0.  If CL inline-expands the intrinsic or reorders
//   the loads, fall back to naked asm (v1 keeps plain C).
extern char *strncpy(char *dst, char *src, int n);

void __stdcall Strncpy(char *dst, char *src, int n)
{
    strncpy(dst, src, n);
    dst[n] = 0;
}