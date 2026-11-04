/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0x999e0
 * (?ParseStrForModemName@@YAJPAE0@Z cdecl, 166 B code + 10 B census tail
 * 8d4900 + 8da424..). CL output is discarded by the fitobj rebuild; husk
 * must merely keep a .text section alive (non-static, else /O2 drops the TU).
 *
 * Semantics: trigram token parser, ebx = state, edi = src index, ebp = dst
 * count, [esp+0x10] = done flag, [esp+0x14] = quit flag. Entry: if *src==0
 * or done or edi>=0x50 -> exit (set both flags = 1). State 0: !isspace(c)
 * -> state 1; skip. State 1: char == '\"' -> state 2. State 2: copy c into
 * arg2[ebp++] while c != '\"' and c >= 0x20. Single isspace call at +0x40.
 */
int w46h_parsestrformodemname_stub(void) { return 0; }