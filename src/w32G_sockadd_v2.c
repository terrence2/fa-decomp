struct socket_state {
	int fd;
	char z1[8];
	int f1;
	int f2;
	char z2[4];
	unsigned char inuse;
	char z3[3];
	int (*fn)(unsigned long, int, int *, struct socket_state *);
};
struct SOCKET_STATE_LIST {
	char z[4];
	int count;
};
extern struct SOCKET_STATE_LIST socket_list;
extern void *w32g_alloc(void);
extern void w32g_cfm(void *p);
char __cdecl socket_add_state_func(unsigned long a, int (__cdecl *fn)(unsigned long, int, int *, struct socket_state *), int st)
{
	struct socket_state *p;
	if (socket_list.count >= 0x40) return 0;
	p = (struct socket_state *)w32g_alloc();
	p->f1 = (int)a;
	p->fn = fn;
	p->f2 = st;
	p->inuse = 1;
	p->fd = -1;
	w32g_cfm(p);
	return 1;
}
