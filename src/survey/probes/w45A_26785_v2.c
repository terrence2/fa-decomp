/* w45A_26785_v2 - rva 0x26785 naked transcription (CL folds *14 into leas + frame) */
extern char w45a_mf[];

void __declspec(naked) _w45a_26785(void)
{
    __asm {
        imul    edx, edx, 0xe
        add     edx, OFFSET w45a_mf
        mov     ax, word ptr [edx+6]
        mov     word ptr [ecx+0x1a], ax
        mov     ax, word ptr [edx+8]
        mov     word ptr [ecx+0x1c], ax
        mov     ax, word ptr [edx+0xa]
        mov     word ptr [ecx+0x1e], ax
        mov     dl, byte ptr [edx+0xc]
        mov     byte ptr [ecx+0x20], dl
        ret
    }
}