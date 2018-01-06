#ifndef __STRING_H__
#define __STRING_H__

#include "types.h"

int memcmp(const void* s1, const void* s2, size_t n);

void* memmove(void* dst, const void* src, size_t n);

void* memset(void* dst, char c, size_t n);

size_t strlen(const char* s);

#endif
