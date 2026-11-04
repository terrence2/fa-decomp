/* _RMFree@4 @ rva 0xa3b80 (128 B) -- v2.
 * Same as v1 (1 byte from EXACT: CL emitted [edi+0x10] where FA has
 * [edi+0x0f] because struct alignment pushed the handle dword). Fix: hd is
 * now a char[4] at +0xf and reads go through a cast. */
struct W37H_RES { char p[0xe]; unsigned char flg; char hd[4]; };
extern char w37h_resFlag;   /* ?resList@@3PAURES_LIST@@A+0x67ec */
extern char w37h_fixStr;    /* ?fixupShape@@3DA+0x2c */
int __fastcall RMFind(char* name);
int __fastcall RMType(struct W37H_RES* h);
void __fastcall MMFreeHandle(unsigned long h);
void __fastcall MMFreePtr(unsigned long h);
void __stdcall RMUnlocate(char* name);
void SMCallByName(char* buf, char* name, int type, struct W37H_RES* h);

void __stdcall RMFree(char* name)
{
    char buf[4];
    struct W37H_RES* h = RMFind(name);
    if (h == 0)
        return;
    if (h->flg & 1) {
        w37h_resFlag = 0;
        SMCallByName(&buf[3], &w37h_fixStr, RMType(h), h);
        if (buf[3] == 0) {
            if (h->flg & 2)
                MMFreeHandle(*(unsigned long*)h->hd);
            else
                MMFreePtr(*(unsigned long*)h->hd);
        }
        w37h_resFlag = 1;
    }
    RMUnlocate(name);
}