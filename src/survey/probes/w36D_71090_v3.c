/* w36D_71090_v3: same body as v1 (v2's y-first spelling is also
   canonicalized by CL 4.2 to cmp y,x + jle + setl); uses 3 1-B/2-B patches
   to restore FA's cmp x,y / jge / setg spellings (w33g precedent):
   0x11,2: 3b ca -> 3b d1 (cmp ecx,edx -> cmp edx,ecx, reg-first)
   0x1f,1: 0x7e -> 0x7d   (jle -> jge, polarity rides the swap; dist 0x07)
   0x21,2: 0f 9c -> 0f 9f (setl al -> setg al) */
int w36d_71090(int a1, int a2)
{
    int x = *(int *)(((char *)a2) + 3);
    int y = *(int *)(((char *)a1) + 3);
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}