// @MISSIONEnsureLegalName@4 @ rva 0x84a60 (96 B) — FA asm (fastcall, ebp
//   frame): 53 56 (push ebx,esi)/8a 01 (mov al,[ecx] — entry guard load)/
//   57 55 (push edi,ebp)/8b f1 (mov esi,ecx)/33 db (xor ebx,ebx=i)/
//   3a c3 (cmp al,bl)/74 4d (je exit)/ loop: 8a 04 1e (mov al,[esi+ebx])/
//   8d 2c 1e (lea ebp,[esi+ebx]=p)/3c 2e 74 04 3c 5e 75 36 (cmp al,'.' / je
//   Lch / cmp al,'^' / jne cont)/ Lch: 8a 45 01 (mov al,[p+1])/
//   8d 55 01 (lea edx,[p+1])/cmp al,20/09/0a/0d je cont/84 c0 je cont/
//   8b fe (mov edi,esi)/b9 -1/2b c0/f2 ae (repne scasb — inline strlen)/
//   f7 d1 (not ecx)/49 (dec ecx)/2b cb (sub ecx,ebx = strlen-i)/
//   4b (dec ebx = i--)/51 52 55 e8 _memmove (push count/src/dst; dst=ebp)/
//   83 c4 0c/ cont: 8a 44 1e 01 (mov al,[esi+ebx+1])/43 (inc ebx)/
//   84 c0 (test al,al)/75 b3 (jne loop)/ exit: 5d 5f 5e 5b c3.
//   Deletes '.'/'^' runs followed by a blank in the mission name IN PLACE:
//   after memmove the index STAYS (i-- before the call bottoms out as i++
//   at cont) so the shifted char at i is re-examined.  Naked-asm escape:
//   plain C probes (b20b_meln_v1/v2, v3 with the explicit i--) flip the
//   register plan — v3 kept i in ebp, computed the src in eax and lost the
//   4b dec-ebx/8a 44 1e 01 forms; C-unreachable same-plan tell as the
//   ctype family.  Probe build/w4probe/b20b_meln_v4.obj — exact modulo the
//   call rel32 window.
extern void __cdecl memmove(void *dst, const void *src, unsigned count);

__declspec(naked) void __fastcall MISSIONEnsureLegalName(char *name)
{
    __asm {
        push ebx
        push esi
        mov al, byte ptr [ecx]
        push edi
        push ebp
        mov esi, ecx
        xor ebx, ebx
        cmp al, bl
        je Lexit
    Ltop:
        mov al, byte ptr [esi+ebx]
        lea ebp, [esi+ebx]
        cmp al, 0x2e
        je Lch
        cmp al, 0x5e
        jne Lcont
    Lch:
        mov al, byte ptr [ebp+1]
        lea edx, [ebp+1]
        cmp al, 0x20
        je Lcont
        cmp al, 9
        je Lcont
        cmp al, 0x0a
        je Lcont
        cmp al, 0x0d
        je Lcont
        test al, al
        je Lcont
        mov edi, esi
        mov ecx, -1
        sub eax, eax
        repne scasb
        not ecx
        dec ecx
        sub ecx, ebx
        dec ebx
        push ecx
        push edx
        push ebp
        call memmove
        add esp, 0xc
    Lcont:
        mov al, byte ptr [esi+ebx+1]
        inc ebx
        test al, al
        jne Ltop
    Lexit:
        pop ebp
        pop edi
        pop esi
        pop ebx
        ret
    }
}