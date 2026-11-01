// @Delete@4 @ rva 0xaa0e0 (48 B) — fastcall ecx = filename: arg pushed as
//   push ecx before mov esi,ecx (esi holds it across the calls), ff 15
//   DeleteFileA; failure writes dosError = -1 (66 c7 word 0xffff) and
//   returns, success 0 then cdecl LibUpdate(name) (add esp,4 after).
__declspec(dllimport) int __stdcall DeleteFileA(const char *fn);
extern void __cdecl LibUpdate(const char *fn);
extern short dosError;

void __fastcall Delete_q(char *fn)
{
    if (!DeleteFileA(fn))
    {
        dosError = -1;
        return;
    }
    dosError = 0;
    LibUpdate(fn);
}