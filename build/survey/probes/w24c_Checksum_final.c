// @Checksum@8 @ rva 0x119f0 (72176 DEC; off 69104) (80 B) — EXACT winner
// (probe w24c_Checksum_v12.c). Naked-asm escape; NO maps, NO patches, 0 relocs.
//
// FA asm (68 B body + census tail 0500000000+8da42400000000 = 12 B):
//   sub esp,8 / mov eax,edx / dec edx / test eax,eax / mov [esp+4],ecx
//   (park fastcall p) / push ebx / mov dword [esp+4],0 (park sum AFTER the
//   push — same slot is [esp+8] pre-push) / je L2 (n==0 skip) / loop:
//   ror dword [esp+4],3 (in-slot RMW rotate of sum) / mov eax,[esp+8] (p)
//   / xor ecx,ecx / mov ebx,[esp+4] (sum reload) / inc eax / mov [esp+8],eax
//   (p++) / mov cl,[eax-1] (deref byte) / add ebx,ecx / mov ecx,edx / dec
//   edx / mov [esp+4],ebx (sum store) / test ecx,ecx / jne loop; L2: mov
//   eax,[esp+4] / pop ebx / add esp,8 / ret (plain c3: fastcall @8 but no
//   stack args — callee pops nothing).
//
// WALL (why naked asm): FA keeps BOTH loop locals (sum, p) parked in esp
// slots with an in-slot RMW rotate; CL 4.2 /O2 register-caches the
// accumulator across the *p deref in every C spelling tried (v1..v11, 32 B
// folded form; both-volatile v8 = 66 B got sum+p parked but the rotate came
// out c1c9xx in-register 3-instr or reg-rotate forms, sum-init pre-push,
// stores re-ordered). Unsteerable in pure C; named wall = in-slot RMW with
// slot-reused init across the push. Naked __declspec(naked) __fastcall with
// the body verbatim; function named `Checksum` so the fastcall mangle is
// the FA chunk name itself — fitobj needs no map. CL text == FA body
// byte-for-byte on first compile (MASM even emits 74/75 short jccs and
// single-byte 4a/40/8a48ff forms identically).
//
// Fit line:
//   python3 tools/fitobj.py build/survey/probes/w24c_Checksum_v12.obj 72176 \
//     build/survey/probes/w24c_Checksum_v12_fit.obj
__declspec(naked) unsigned long __fastcall Checksum(const void *pv, unsigned long n)
{
    __asm {
        sub     esp, 8
        mov     eax, edx
        dec     edx
        test    eax, eax
        mov     [esp+4], ecx
        push    ebx
        mov     dword ptr [esp+4], 0
        je      L2
L1:
        ror     dword ptr [esp+4], 3
        mov     eax, [esp+8]
        xor     ecx, ecx
        mov     ebx, [esp+4]
        inc     eax
        mov     [esp+8], eax
        mov     cl, [eax-1]
        add     ebx, ecx
        mov     ecx, edx
        dec     edx
        mov     [esp+4], ebx
        test    ecx, ecx
        jne     L1
L2:
        mov     eax, [esp+4]
        pop     ebx
        add     esp, 8
        ret
    }
}