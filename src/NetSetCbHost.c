extern unsigned char callbacks[];
void net_set_callback_host(void *cb, void *data)
{
    *(void **)(callbacks + 4) = data;
    *(void **)(callbacks + 0) = cb;
}