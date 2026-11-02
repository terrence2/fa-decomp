extern unsigned char callbacks[];
void net_set_callback_players(void *cb, void *data)
{
    *(void **)(callbacks + 0xc) = data;
    *(void **)(callbacks + 8) = cb;
}