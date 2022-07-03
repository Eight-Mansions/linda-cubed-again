#ifndef FONT_H_
#define FONT_H_

#include "platform.h"

extern "C" {

	u32 curLetIdx;

	u32 GetLetterWidth(u32 letter);

	u32 GetSentenceWidth(const u16* text, const u16* end);

	//int GetYForCentering(const char* text, u32 length);
}

#endif