/* w31H_b3c90 v1: FA bytes (rva 0xb3c90, 30 B code + 2 B pad): mov eax,[esp+4];
   push ebx; push 0x82; push 0; push eax; mov ebx,[eax+4]; call [ebx];
   add esp,0xc; mov BYTE PTR [eax+0x80],0; pop ebx; ret.
   (dis.py elided the 7-B c6 80 80 00 00 00 00 store — from raw FA.)
   cdecl; callee reached through vtable ptr at [p+4], method 0; caller cleans
   (cdecl target, 3 args); post-call [eax+0x80]=0 store reuses eax (callee
   returns the arg pointer). Modeled as COM-style p->vt->m0 so CL emits
   mov ebx,[eax+4]; call [ebx]. */
typedef void *(__cdecl *W31H_FP)(void *, long, long);
struct W31H_V { W31H_FP m0; };
struct W31H_O { char pad[4]; struct W31H_V *vt; };
void w31h_4b3c90(struct W31H_O *p)
{
    void *q = p->vt->m0(p, 0, 0x82);
    ((unsigned char *)q)[0x80] = 0;
}