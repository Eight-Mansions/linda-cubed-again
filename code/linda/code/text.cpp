#include "text.h"
#include <ctype.h>

int ConvertToLower(char* left, char* right, int len)
{
	char l[12];
	char r[12];

	for (int i = 0; i < len; i++)
	{
		l[i] = (left[i] <= 'Z' && left[i] >= 'A') ? left[i] - ('Z' - 'z') : left[i];
		r[i] = (right[i] <= 'Z' && right[i] >= 'A') ? right[i] - ('Z' - 'z') : right[i];
	}

	int isEqual = strncmp(l, r, len);

	return isEqual;
}