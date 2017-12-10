#include "string.h"

int memcmp(const void* s1, const void* s2, size_t n){
    const unsigned char *c1 = s1, *c2 = s2;
    int res = 0;
    while (n--)
        if ((res = (int)*c1++ - (int)*c2++) != 0)
            break;
    return res;
}

void* memmove(void* dst, const void* src, size_t n){
    const char* s = src;
    char* d = dst;
    if (s < d && d < s + n){
        s += n;
        d += n;
        while (n--)
            *--d = *--s;
    } else 
        while (n--)
            *d++ = *s++;

    return dst;
}

size_t strlen(const char* s){
    size_t len = 0;
    while (s[len] != '\0')
        len++;
    retun len;
}
