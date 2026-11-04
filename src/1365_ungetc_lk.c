/* wave-40C probe v2: __ungetc_lk - shared fail exit, FA test chain */
typedef struct {
    int _ptr;      /* +0 */
    int _cnt;      /* +4 */
    int _base;     /* +8 */
    int _flag;     /* +0xc */
    int _file;     /* +0x10 */
    int _charbuf;  /* +0x14 */
    int _bufsiz;   /* +0x18 */
} FILEX40;

int _t4dc580(FILEX40 *);  /* still-stub anchor $FA$_t_4dc580 */

int __ungetc_lk(int cb, FILEX40 *str)
{
    FILEX40 *s;
    int eax;

    if (cb == -1)
        goto fail;
    s = str;
    if (s->_flag & 1)
        goto ok;
    if (!(s->_flag & 0x80))
        goto fail;
    if (s->_flag & 2)
        goto fail;
ok:
    if (s->_base == 0)
        _t4dc580(s);
    eax = s->_ptr;
    if (s->_base == eax) {
        if (s->_cnt) {
            return -1;
        } else {
            s->_ptr = eax + 1;
        }
    }
    eax = s->_ptr;
    if (*(char *)&s->_flag & 0x40) {
        s->_ptr = eax - 1;
        if (*(char *)eax == (char)cb)
            goto have;
        s->_ptr = eax + 1;
        return -1;
    } else {
        s->_ptr = eax - 1;
        *(char *)eax = (char)cb;
    }
have:
    s->_cnt++;
    eax = s->_flag;
    s->_flag = eax & 0xffffffef;
    eax = s->_flag;
    s->_flag = eax | 1;
    return cb & 0xff;
fail:
    return -1;
}