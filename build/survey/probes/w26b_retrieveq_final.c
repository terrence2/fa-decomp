// ?retrieveFromQueue@@YAXAAUSERIAL_QUEUE@@JAAUSERIAL_PACKET_WRAPPER@@@Z @ 0x984d0 — naked asm v1
struct SQP { long r0, r1, divisor, r3, r4, r5; unsigned long *baseh; };
__declspec(naked) void __cdecl retrieveFromQueueq(struct SQP *q, long l, void *out)
{
    __asm
    {
        mov eax, [esp+8]
        push esi
        mov ecx, [esp+8]
        push edi
        cdq
        mov esi, [ecx+14h]
        mov edi, [esp+14h]
        idiv dword ptr [ecx+8]
        shl edx, 4
        mov ecx, 0Ch
        lea edx, [edx+edx*2]
        add esi, edx
        rep movsd
        pop edi
        pop esi
        ret
    }
}
