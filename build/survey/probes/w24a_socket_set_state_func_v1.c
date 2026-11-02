void socket_set_state_func(void *s, long f, long st)
{
    *(long *)((char *)s + 0x10) = st;
    *(long *)((char *)s + 0x1c) = f;
}
