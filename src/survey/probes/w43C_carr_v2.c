/* _CARRIERProc (112 B) - 8-way uchar jump-table dispatch returning handler
   addresses (b8 imm32 + rel fixup, masked in the judge) or the OBJProc
   forwarding call (push c / call _OBJProc / add esp,4 / c3).
   v2: case 1 omitted -> its table slot shares the default body (FA's
   compiler shares the identical zero block; CL 4.2 does the same when the
   case is omitted and default is written inside the switch). */
extern long __cdecl w43c_c0q(char *p);          /* $FA$_t_4b9ed0 */
extern long __cdecl w43c_c2q(char *p);          /* $FA$_t_4b99c0 */
extern long __cdecl GVEventProc(char *p);       /* _GVEventProc @ 0x472ea0 */
extern long __cdecl w43c_objw(char c);          /* _OBJProc @ 0x472b30 */
extern long __cdecl NPCWeaponsProc(char *p);    /* _NPCWeaponsProc @ 0x472640 */
extern long __cdecl SAYDefaultSayProc(char *p); /* _SAYDefaultSayProc @ 0x48b520 */
extern long __cdecl APCommentProc(char *p);     /* _APCommentProc @ 0x48d800 */
long CARRIERProc(unsigned char c)
{
    switch (c) {
    case 0: return (long)w43c_c0q;
    case 2: return (long)w43c_c2q;
    case 3: return (long)GVEventProc;
    case 4: return w43c_objw(c);
    case 5: return (long)NPCWeaponsProc;
    case 6: return (long)SAYDefaultSayProc;
    case 7: return (long)APCommentProc;
    default: return 0;
    }
}