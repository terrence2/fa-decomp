// _OBJAliasForMulti@0 @ rva 0x8f8e0 = 588000, 80 B (FA: push esi; eax=
//   [numComputers]; push edi; cmp eax,1; je Lend; mov WORD
//   [?COMMENT_TYPE+0x864],0xd508; mov di,1; cmp WORD [_nextObjId],di;
//   jbe Lend; Ltop: eax=edi; and eax,0xffff; esi=[eax*4+_objPtrs]; if
//   WORD [esi+0x74]==0: call OBJNextAliasForMulti; mov WORD [esi+0x74],ax;
//   inc di; cmp WORD [_nextObjId],di; ja Ltop; Lend: pop edi; pop esi; ret).
extern unsigned int w26_numComputers; /* map _w26_numComputers=_numComputers */
extern unsigned short w26_commentW; /* map _w26_commentW=?COMMENT_TYPE@@3W4__unnamed@@A+0x864 */
extern unsigned short w26_aliasCnt; /* map _w26_aliasCnt=_nextObjId */
extern void *w26_objPtrs2[]; /* map _w26_objPtrs2=_objPtrs */
extern unsigned short __fastcall OBJNextAliasForMultiQ(void); /* map @OBJNextAliasForMultiQ@0=@OBJNextAliasForMulti@0 */

void __cdecl w26c_OBJAliasForMulti_q(void)
{
    unsigned short i;
    if (w26_numComputers == 1) return;
    w26_commentW = 0xd508;
    i = 1;
    while (w26_aliasCnt > i) {
        unsigned char *o = (unsigned char *)w26_objPtrs2[i];
        if (*(unsigned short *)(o + 0x74) == 0)
            *(unsigned short *)(o + 0x74) = OBJNextAliasForMultiQ();
        i++;
    }
}