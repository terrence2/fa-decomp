// ?RemapInsignia@@YIXPAUT_BITMAP@@@Z @ rva 0x66b50 (48 B) — FA asm: push ebx /
//   edx=[ecx+0xa] / push ebp / eax=[ecx+0xe] / add eax,edx / cmp eax,edx /
//   jbe done / xor ebx,ebx / L: mov eax,[insigniaRemap] / mov bl,[edx] / inc edx
//   / mov al,[ebx+eax] / mov [edx-1],al / mov eax,[ecx+0xa] / add eax,[ecx+0xe]
//   / cmp eax,edx / ja L / done: pop ebp / pop ebx / ret. Fastcall T_BITMAP*:
//   remap insigne bytes through the remap table. Plain C: the per-iteration
//   reloads of the remap POINTER (a1 in-loop) and of the end pointer (re-read
//   [ecx+0xa]/[ecx+0xe]) are CL's own aliasing reloads — *p stores may alias;
//   the xor ebx,ebx + mov bl,[edx] pair is a zero-initialized byte local
//   (unsigned char c = 0) partially written per iteration; inc edx scheduled
//   between load and [edx-1] store by CL. push ebp comes out of CL naturally.
extern unsigned char *insigniaRemapP;   // -> ?insigniaRemap@@3PAEA

void __fastcall RemapInsignia_q(char *tb)
{
    unsigned char *p = *(unsigned char **)(tb + 0xa);
    unsigned char c = 0;
    while (p < *(unsigned char **)(tb + 0xa) + *(unsigned long *)(tb + 0xe)) {
        c = *p;
        *p = insigniaRemapP[c];
        p++;
    }
}