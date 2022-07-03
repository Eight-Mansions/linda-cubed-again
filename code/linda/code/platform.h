#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <stdint.h>
#include "core.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

void itoa(i32 i, char b[]);
void itox(u32 i, char* s);

extern "C" {
	extern int printf(const char* fmt, ...);
}
#endif