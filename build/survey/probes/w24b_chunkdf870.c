/* probe v1: push 2; call __amsg_exit; add esp,4; ret */
extern void _amsg_exit(int n);
void w24b_chunkdf870(void) { _amsg_exit(2); }
