/* probe v1: push -3; call __setmbcp; add esp,4; ret */
extern void _setmbcp(int n);
void w24b_chunkd9e30(void) { _setmbcp(-3); }
