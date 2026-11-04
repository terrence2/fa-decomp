/* _CTDo_rudder @ rva 0x64de0 (112 B) -- v4: FA carries BOTH clamps as an
 * if/else whose then-arm is FA's 9-B 'mov WORD PTR [X],0x71c' immediate
 * store (hidden in dis.py elision) and whose else-arm re-stores v before
 * the -1820 (0xf8e4) test. Raw-hexdump structure per 49-B block:
 *   call; store v; cmp 0x71c; jle else; store-imm 0x71c; jmp join;
 *   else: store v; cmp 0xf8e4; jge join; store-imm 0xf8e4; join.
 * Block 2's two arms end in plain ret (function end). */
extern short __cdecl w37c_ctda(void);
extern short w37c_stfc;             /* _serviceTicks+0xfc */
extern short w37c_stw100;           /* _serviceTicks+0x100 */

void w37c_rudder(void)
{
    short v;

    v = w37c_ctda();
    w37c_stfc = v;
    if (v > 1820)
        w37c_stfc = 1820;
    else if (v < -1820)
        w37c_stfc = -1820;
    v = w37c_ctda();
    w37c_stw100 = v;
    if (v > 1820)
        w37c_stw100 = 1820;
    else if (v < -1820)
        w37c_stw100 = -1820;
}