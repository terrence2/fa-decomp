// @Abs@4 @ rva 0xc29c4 (12 B) — abs of a short fastcall arg:
//   movsx eax, cx / cdq / xor eax, edx / sub eax, edx / ret
// Plain C `v < 0 ? -v : v` reproduces the cdq/xor/sub idiom (w14c_ab1,
// byte-exact; ab2 if/return form re-emits with a c3/c3 tail instead).
int __fastcall Abs(short v)
{
    return v < 0 ? -v : v;
}
