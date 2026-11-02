// w26a_validate @ rva 0xae240 (714304) ?validate_player@@YAPAU_player_info@@J@Z
// (48 B) — FA bytes (raw cross-check; dis.py elides the 7-byte sib load and
// invents an "n==0" test that is really the p==0 test after the tab load):
//   8b 44 24 04          mov eax,[esp+4]           (n)
//   85 c0                test eax,eax
//   7c 1f                jl  L_b                   (ret0 #2 at +0x27)
//   8b 0d 4c 7e 57 00    mov ecx, ds:0x577e4c      (player_list+4, count)
//   3b c8                cmp ecx,eax
//   7e 15                jle L_b
//   8b 04 85 ae 7e 57 00 mov eax, ds:[eax*4 + 0x577eae]   (p = tab[n],
//                                 table at player_list+0x66)
//   85 c0                test eax,eax
//   74 07                je  L_a                   (ret0 #1 at +0x24)
//   8a 48 36             mov cl,[eax+0x36]
//   84 c9                test cl,cl
//   75 05                jne L_p                   (L_p: bare ret, eax=p)
// L_a: 33 c0 c3         xor eax,eax / ret
// L_b: 33 c0 c3         xor eax,eax / ret
// L_p: ret              (eax = p)
//   + census pad "8d9b00000000" (6 B)
extern char player_list_t[];   /* ?player_list@@3UNET_PLAYER_LIST@@A */
typedef void *pl;
pl w26a_validate(long n)
{
    if (n < 0 || *(long *)(player_list_t + 4) <= n)
        return 0;
    {
        pl p = *(pl *)(player_list_t + 0x66 + 4 * n);
        if (p == 0 || *(char *)((char *)p + 0x36) == 0)
            return 0;
        return p;
    }
}