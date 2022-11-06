#ifndef TEXT_H_
#define TEXT_H_

#include "platform.h"

extern "C" {
	extern int strncmp(char* left, char* right, int len);

	int ConvertToLower(char* left, char* right, int len);
}

#endif