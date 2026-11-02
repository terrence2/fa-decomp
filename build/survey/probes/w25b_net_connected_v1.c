extern unsigned char callbacks[];
void net_set_callback_connected(void *cb, void *data)
{
    *(void **)(callbacks + 0x14) = data;
    *(void **)(callbacks + 0x10) = cb;
}