/* w46H wave-46 batch H: whole-body transplant husk for FA rva 0xb96b0
 * (_APClearParks@0 fpo/esp, 186 B code + 6 B census tail 8d9b00000000). CL
 * output is discarded by the fitobj rebuild; husk must merely keep a .text
 * section alive (non-static, else /O2 drops the TU body).
 *
 * Semantics: walk _airports (count == _numAirports, airport stride via 9-8-4
 * lea chain = *0x4c) zeroing [+0x111 .. +0x11c] (4 dwords + word) then
 * advancing 0x134 per element (cmp edx,esi loop with the eax/ecx pointer
 * carried in si-params style). Then for i < _numPlanes: cx = word[_planes+2i]
 * -> @OBJGet@4; cl = obj[0xe3]; class-window ladder (cl<1 jb, cl<=0x12 jbe,
 * cl<0x13 jb, cl<=0x1e jbe) -> clear that plane's park fields.
 */
int w46h_apclearparks_stub(void) { return 0; }