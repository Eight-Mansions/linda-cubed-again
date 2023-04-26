#ifndef FONT_H_
#define FONT_H_

#include "platform.h"

extern "C" {
	static bool vwfOn = true;

	static u32 currentLetter = 0;

	void SetLetter(const u32 letter);

	u16 GetRegularLetterWidth(u16 defaultWidth);

	u16 GetBabyLetterWidth(u16 defaultWidth);
}

#endif