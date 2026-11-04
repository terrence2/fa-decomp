/* STRIPProc: switch remap table dispatcher (two-level: cl byte map + jump
   table). Cases 0/3/6/7 return FA proc addresses; default returns 0. */
extern long __cdecl STRIPAddProc(void);
extern long __cdecl OBJEventProc(void);
extern long __cdecl SAYDefaultSayProc(void);
extern long __cdecl APCommentProc(void);

long __cdecl STRIPProc(unsigned char x)
{
    switch (x) {
    case 0: return (long)STRIPAddProc;
    case 3: return (long)OBJEventProc;
    case 6: return (long)SAYDefaultSayProc;
    case 7: return (long)APCommentProc;
    }
    return 0;
}
