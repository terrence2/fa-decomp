/* @MainMenu@4 @ rva 0x9e880 */
extern unsigned short MenuUpdateQ(void);
extern void __fastcall CampaignMenu(unsigned short r);
extern void __stdcall MaybeExitToDOS(void);

unsigned short __fastcall MainMenu(unsigned short key)
{
    unsigned short r;

    if (key == 0x3e04)
        r = 0x101;
    else
        r = MenuUpdateQ();

    if (r != 0) {
        if ((unsigned char)(r >> 8) == 2)
            CampaignMenu(r);
        else if (r == 0x101)
            MaybeExitToDOS();
    }
    return r;
}