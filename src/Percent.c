// @Percent@4 @ rva 0x557c0 — push esi / mov si,cx / mov ecx,100 / call
//   @Rand@4 / cmp si,ax / pop esi / setl cl / mov al,cl / ret (probe w1:
//   the signed-short compare `x > Rand(100)` compiles as cmp ax,si; setl).
extern short __fastcall Rand(int a);

char __fastcall Percent(short x)
{
    return (char)(x > Rand(100));
}
