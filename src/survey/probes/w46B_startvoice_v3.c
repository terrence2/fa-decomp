/* w46B_startvoice_v3 - ?StartVoice@@YAXPAUMODSPEC@@G@Z, FA rva 0x354b0 (218288), 128 B, tail 8d4900 (3-B lea census filler)
 *
 * v1 diffs: struct padding (+2 offsets), no push ebp, edi=n SIB loads instead of
 * lea edi + [edi] derefs, direct IAT e8 rel32 instead of imp maps.
 * v2 levers: #pragma pack(1); __declspec(dllimport) decls (w27c precedent ->
 * __imp__X@N FROMs); pLoopCount/pAddr function-pointer locals = FA's ebp
 * reg-indirect IAT calls (mov ebp,[IAT]; ff d5) AND the push ebp in the prolog;
 * (void**)&mchA[n] type-pun so CL can't CSE *hp against the SIB load.
 */
#pragma pack(push, 1)
typedef void (__stdcall *AIL_SVLC)(void *h, long n);
typedef void (__stdcall *AIL_SADDR)(void *h, void *addr, unsigned long len);
typedef struct {
    unsigned char pad00[0x0e];
    unsigned long off0e;            /* MMAccessR index -> sample addr */
    unsigned char pad12[0x22-0x12];
    unsigned long off22;            /* set_sample_address length */
    unsigned char pad26[0x4a-0x26];
    unsigned char off4a;            /* loop-count flag */
} MODSPEC;
#pragma pack(pop)

extern void *mchA[];                /* ?mixChanHandle@@3PAPAU_SAMPLE@@A */
extern __declspec(dllimport) void * __stdcall _AIL_init_sample(void *h);
extern __declspec(dllimport) void * __stdcall _AIL_set_sample_loop_count(void *h, long n);
extern __declspec(dllimport) void * __stdcall _AIL_set_sample_address(void *h, void *addr, unsigned long len);
extern __declspec(dllimport) void * __stdcall _AIL_set_sample_type(void *h, long t1, long t2);
extern __declspec(dllimport) void * __stdcall _AIL_start_sample(void *h);
extern void * __fastcall MMAccessR(long idx);
extern void __fastcall SetVolPitchPan(MODSPEC *mod, unsigned short idx);

void StartVoice(MODSPEC *mod, unsigned short idx)
{
    unsigned n;
    void *h;
    void **hp;
    AIL_SVLC pLoopCount;
    AIL_SADDR pAddr;
    n = idx & 0xffff;
    h = mchA[n];
    hp = (void **)((char *)mchA + (n << 2));
    _AIL_init_sample(h);
    pLoopCount = (AIL_SVLC)_AIL_set_sample_loop_count;
    pLoopCount(*hp, mod->off4a ? 1 : 0);
    pAddr = (AIL_SADDR)_AIL_set_sample_address;
    pAddr(*hp, MMAccessR(mod->off0e), mod->off22);
    _AIL_set_sample_type(*hp, 0, 0);
    SetVolPitchPan(mod, idx);
    _AIL_start_sample(*hp);
}