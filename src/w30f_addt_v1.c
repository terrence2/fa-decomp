/* w30f addT @ rva 0x6dcf0 (dec 449776), 32 B (26 B code + 6 B pad)
 * FA:
 *   66 81 f9 ff 7f  cmp cx,0x7fff
 *   74 0f           je L
 *   66 85 c9        test cx,cx
 *   74 0a           je L
 *   66 a1 18 9e 54 00  mov ax,ds:_currentT
 *   66 03 c1        add ax,cx
 *   c3              ret
 * L: 66 8b c1       mov ax,cx
 *   c3              ret
 * fastcall short param in cx, 16-bit global.
 */
extern short _currentT;

short __fastcall w30f_addt_v1(short t)
{
    if (t == 0x7fff || t == 0)
        return t;
    return t + _currentT;
}