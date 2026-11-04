/* w35G 0x43fd0 (32 B, unnamed) v1 — double-deref vtable call (w34g bba80 recipe)
 * FA 24 B code + 8 B tail (8d642400 x2):
 *   mov eax,[esp+4] / push ebx / push eax / mov ecx,[eax]
 *   / mov DWORD [ecx+0x14],0x30 / mov ebx,[eax] / call DWORD [ebx]
 *   / add esp,4 / pop ebx / ret
 * store (*(int**)a)[5] = 0x30; cdecl 1-arg vtable call through **(void**)a.
 */
void w35G_43fd0(void *a)
{
    (*(long **)a)[5] = 0x30;
    (void)(*(void (__cdecl **)(void *))*(void **)a)(a);
}