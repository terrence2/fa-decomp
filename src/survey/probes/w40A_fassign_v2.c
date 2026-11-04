/* w40A_fassign_v2 — __fassign 0xd94f0 (76 B): two locals at top (f +0, d +4) */
void __cdecl __atodbl(void* val, char* str);
void __cdecl __atoflt(void* val, char* str);

void __cdecl __fassign(int flag, void* pval, char* str)
{
    float f;
    double d;
    if (flag) {
        __atodbl(&d, str);
        *(double*)pval = d;
    } else {
        __atoflt(&f, str);
        *(float*)pval = f;
    }
}