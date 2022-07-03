#include "platform.h"

void itoa(i32 i, char b[]) {
    char const digit[] = "0123456789";
    char* p = b;
    if (i < 0) {
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do { // Move to where representation ends
        ++p;
        shifter = shifter / 10;
    } while (shifter);
    *p = '\0';
    do { // Move back, inserting digits as u go
        *--p = digit[i % 10];
        i = i / 10;
    } while (i);
}

void itox(u32 i, char* s) {
    unsigned char n;
    s += 8;
    *s = '\0';
    for (n = 8; n != 0; --n) {
        *--s = "0123456789ABCDEF"[i & 0x0F];
        i >>= 4;
    }
}
