/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0x51080
 * (_LimitThrottle@0 fpo/esp, 153 B code + 7 B census tail 8da424..). CL
 * output is discarded by the fitobj rebuild; husk must merely keep a .text
 * section alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: esi = 100; if byte[_curThing+0x10] & 0x80: esi -= byte[_dam+0x82].
 * Both branches then: HARDTotalFuel() + dword[_curThing+0x1fc] == 0 -> esi=0
 * (duplicated jne/je structure with shared tail). Then word[_curThing+0x20f]
 * vs curThingType+0x14d clamp chain (jl/jge/je ladder at +0x7a) lowers esi;
 * returns esi.
 */
int w46h_limitthrottle_stub(void) { return 0; }