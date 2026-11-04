// _StreamersShutdown@0 @ rva 0x9e2f0 (64 B) — FA asm: push esi/edi / xor edi,edi
//   / cmp [numPlanes],di / jle exit / xor esi,esi / L: lea ecx,[esi+planes+0x80]
//   / add esi,0x14 / inc edi / call @SampleShutdown@4 / lea ecx,[esi+Ctrl+0x34c]
//   / call / movsx eax,[numPlanes] / cmp eax,edi / jg L / exit: pop edi/esi / ret.
//   Per-plane thiscall pair with one running 0x14 offset shared by both arrays.
//   Plain C: p's initialization sits INSIDE the guard (declared as plain local,
//   assigned after the i<numPlanes test) so FA's xor edi-first / cmp [np],di /
//   xor esi-after-guard order holds; bottom re-test is CL's volatile reload of
//   numPlanes through the SampleShutdown calls. do_streamer_def sibling band.
extern short numPlanes;
extern void __fastcall SampleShutdown(void *p);
extern char strmPlanesA[];   // -> _planes+0x80
extern char strmCtrlB[];     // -> ?Ctrl@@3USERIAL_CONTROL_STRUCTURE@@A+0x34c

void __stdcall StreamersShutdown_q(void)
{
    long p, i = 0;
    if (i < numPlanes) {
        p = 0;
        do {
            SampleShutdown(strmPlanesA + p);
            p += 0x14;
            i++;
            SampleShutdown(strmCtrlB + p);
        } while (i < numPlanes);
    }
}