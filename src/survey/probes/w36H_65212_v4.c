/* _CTDo_yoyo @ rva 0x65212 (110 B) -- v4 naked-asm: fixes v2. FA also
 * materializes the w-word into CX (66 8b 0d) BEFORE the first push and
 * again into AX after it; MASM keeps 8b-0d for cx and 66 a1 for ax. */
extern unsigned short __cdecl w36h_ctda(void);
extern unsigned short __cdecl w36h_ctdb(void);
extern unsigned short __cdecl w36h_ctdc(void);
extern void __stdcall MVRYoyo(int, int, int, int, int);
extern char serviceTicks[];

void __declspec(naked) CTDo_yoyo(void)
{
    __asm {
        push esi
        push edi
        call w36h_ctda
        mov si, ax
        call w36h_ctdb
        mov di, ax
        call w36h_ctdc
        cmp WORD PTR [serviceTicks+0x20], 0
        je Lend
        mov cl, BYTE PTR [serviceTicks+0xec]
        test cl, cl
        jne Lend
        mov cx, WORD PTR [serviceTicks+0x100]
        push eax
        mov ax, WORD PTR [serviceTicks+0x100]
        push edi
        push eax
        push ecx
        push esi
        call MVRYoyo
        mov WORD PTR [serviceTicks+0x100], 0
        mov WORD PTR [serviceTicks+0xfc], 0
        mov eax, 1
        mov BYTE PTR [serviceTicks+0xf0], al
        mov BYTE PTR [serviceTicks+0xf8], al
    Lend:
        pop edi
        pop esi
        ret
    }
}