/* unnamed gap chunk @ rva 0x43fa0 (278432, 16 B) — tail-jump thunk to
 * @MMAllocPtr@8: cdecl 2-param wrapper forwarding param 2 (in ecx) with
 * edx=0, jmp.  Fastcall callee declared; args eval right-to-left gives
 * xor edx,edx / mov ecx,[esp+8] / jmp.  Map FROM @w30e_mmal@8 TO FA's
 * real @MMAllocPtr@8.  Tail pad 05 00 00 00 00 (5 B) census filler.
 */
void * __fastcall w30e_mmal(void *pv, void *pv2);

void * __cdecl w30e_mmthunk(void *pa, void *pb)
{
    return w30e_mmal(pb, 0);
}