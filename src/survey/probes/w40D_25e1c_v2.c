/* w40D_25e1c v2: for loop (rotation should give FA's two differently
 * ordered tests: head cmp [next],si/jbe, tail cmp si,[next]/jb)
 */
typedef unsigned short ushort;
typedef unsigned long ulong;

extern ushort nextObjId;    /* 0x54ad88 */
extern ulong  objPtrs[];    /* 0x54ad98 */

char __fastcall w40d_chk(unsigned short);
void __fastcall w40d_note(int);

void objwalk16(void)
{
    ushort i;
    for (i = 1; (ushort)nextObjId > i; i++)
    {
        if (w40d_chk(i))
        {
            unsigned char *o = (unsigned char *)objPtrs[i];
            unsigned char c = *o;
            if (c == 2 || c == 4)
                w40d_note(*(int *)(o + 0xe4));
        }
    }
}