/* w42E candidate 1 v4: same C as v1 (CL matches FA head/body byte-for-byte);
 * two CL/FA deltas fixed by patches: (a) the *count == -1 gate is FA's
 * cmp [ebp+0],-1 (4 B) vs CL's mov eax,[ebp]+cmp eax,-1+jne (8 B, -2), and
 * the jle loop-exit disp needs FA's 0x17 (final tail 2 B shorter).
 */
extern long w42E_putcl(int ch, void *strm, long *count);

void w42E_d7050(char *p, long n, void *strm, long *count)
{
    while (n-- > 0) {
        w42E_putcl(*p++, strm, count);
        if (*count == -1)
            break;
    }
}