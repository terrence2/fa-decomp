/* @GRPHumansFirst@4 rva 0x5f310, 128 B, no tail pad (c3 at 0x7f).
 * fastcall ecx=g, fpo: sub esp,4 / xor edx,edx (i) / push ebx,esi,edi /
 * mov bl,[gsizes+g] / push ebp / cmp bl,dl; je ret /
 * lea eax,[ecx+ecx*4] lea esi,[eax*2] (10g) / xor eax,eax; mov al,bl; mov [slot],eax (saved) /
 * do { lea eax,[esi+edx]; mov di,[eax*2+gids] (sel); lea ebx,[eax*2+gids] (p);
 *      mov eax,edi; and eax,0xffff; mov ebp,[eax*4+objPtrs] (op);
 *      mov al,[ebp+0x10]; test al,0x80; jskip;
 *      mov eax,edx; test edx,edx; jle skiploop;
 *      shift loop: mov bp,[ebx-2]; sub ebx,2; mov [ebx+2],bp; dec eax; jne;
 *      lea eax,[ecx*4]; mov [eax+eax*4+gids],di (gids[10g]=sel);
 *      inc edx; mov eax,[slot]; cmp edx,eax; jl loop; } epilogue pops+ret */
extern unsigned char w38d_gsizesX[];
extern unsigned short w38d_gidsX[];
extern long w38d_opsX[];

void __fastcall GRPHumansFirst(int g)
{
    unsigned short sel;
    unsigned short *p;
    long op;
    int i, saved, t;
    unsigned char count;

    i = 0;
    count = w38d_gsizesX[g];
    if (!count)
        return;
    saved = count;
    do {
        sel = w38d_gidsX[g * 10 + i];
        p = &w38d_gidsX[g * 10 + i];
        op = w38d_opsX[sel & 0xffff];
        if (*(unsigned char *)(op + 0x10) & 0x80) {
            for (t = i; t > 0; t--) {
                *p = *(p - 1);
                p--;
            }
            w38d_gidsX[g * 10] = sel;
        }
        i++;
    } while (i < saved);
}