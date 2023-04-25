#ifndef FONT_H_
#define FONT_H_

#include "platform.h"

extern "C" {
	static bool vwfOnOff = true;

	static u16 letterWidth = 0;

	u32 curLetIdx;

	u32 GetLetterWidth(u32 letter);

	u32 GetSentenceWidth(const u16* text, const u16* end);

	void UpdateLetterWidthForSmall();

	//int GetYForCentering(const char* text, u32 length);
	
	void SetLetterWidthNew(const u32 letter);

	void SetBabyLetterWidthNew(const u32 letter);

	u16 GetLetterWidthNew(u16 defaultWidth);
}

#endif