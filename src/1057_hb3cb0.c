/* w32C 4b3cb0 v2: unnamed chunk (rva 736432, 0xb3cb0, 32 B incl 2B pad 8bff)
 * FA (rva 0xb3cb0): mov eax,[esp+4]; push ebx; push 0x112; push 0; push eax;
 * mov ebx,[eax+4]; call [ebx]; add esp,0xc; mov byte[eax+0x111],0 (c6 80);
 * pop ebx; ret; 2B pad. Callee-vtable call, edx-free. Must alias
 * "0=$FA$_t_4b3cb0" (t000a8 defines it; refs in t0052c, g0000_$4b1a00,
 * g0000_$4b3ae0). Def name dead; no maps. */
typedef void (__cdecl *W32CB3FN)(void *, long, long);

void w32cB3cb0F2(void *e)
{
    void *p;
    W32CB3FN fn;

    p = e;
    fn = (W32CB3FN)(*(void **)((char *)p + 4));
    (void)fn(p, 0, 0x112);
    *(char *)((char *)p + 0x111) = 0;
}