// w26a_iscomment @ rva 0x99ad0 (629456) ?IsComment@@YAJPAE@Z (64 B) — FA
// bytes (raw cross-check):
//   56                   push esi
//   33 c0                xor eax,eax
//   8b 74 24 08          mov esi,[esp+8]
//   8a 06                mov al,[esi]
//   50                   push eax
//   e8 ........          call _isspace
//   83 c4 04             add esp,4
//   85 c0                test eax,eax
//   74 12                je L0               (skip the skip-leading loop)
//   46                   inc esi
//   33 c0                xor eax,eax
//   8a 06                mov al,[esi]
//   50                   push eax
//   e8 ........          call _isspace
//   83 c4 04             add esp,4
//   85 c0                test eax,eax
//   75 ee                jne (loop head)
// L0: 33 c0              xor eax,eax
//   8a 0e                mov cl,[esi]
//   5e                   pop esi             (restore scheduled before cmp)
//   80 f9 2f             cmp cl,0x2f
//   0f 94 c0             sete al
//   c3                   ret
//   + census pad "0500000000" + "8da42400000000" (12 B)
// Skip leading whitespace, then report s[0]=='/'.
// Lever (round 3): the final predicate must be staged through a long
// local r (return (unsigned char)(c=='/'); emits CL's sete-into-cl copy
// plan, 13 B tail; assigning to a long local schedules FA's 33 c0 xor
// ahead of the cl load and lands sete straight in al, 12 B tail).
extern int __cdecl isspace(int c);
long w26a_iscomment(unsigned char *s)
{
    long r;
    if (isspace(*s)) {
        do {
            ++s;
        } while (isspace(*s));
    }
    r = (*s == '/');
    return r;
}