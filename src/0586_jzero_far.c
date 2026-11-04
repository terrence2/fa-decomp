// ?jzero_far@@YAXPAXI@Z @ rva 0x74fd0 (32 B) — FA asm: mov edx,[esp+8] / push
//   edi / mov edi,[esp+8] / xor eax,eax / mov ecx,edx / shr ecx,2 / rep stosd /
//   mov ecx,edx / and ecx,3 / rep stosb / pop edi / ret. Zero-fill of n bytes.
//   Plain C: memset(dst,0,n) — CL 4.2's /O2 inline expansion IS this exact
//   edx=n-first, rep-stosd + rep-stosb-tail sequence (var-size sibling of the
//   const-size rep stosd idiom from InitTmapRemaps); no #pragma escape needed.
void *memset(void *d, int c, unsigned n);

void jzero_far(void *dst, unsigned n)
{
    memset(dst, 0, n);
}