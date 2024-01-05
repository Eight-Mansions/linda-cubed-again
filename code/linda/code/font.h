#ifndef FONT_H_
#define FONT_H_

#include "platform.h"

extern "C" {
	static bool vwfOn = true;

	static bool kana2romajiOn = true;

	static u32 currentLetter = 0;

	void SetLetter(const u32 letter);

	u16 GetRegularLetterWidth(u16 defaultWidth);

	u16 GetBabyLetterWidth(u16 defaultWidth);

	u16 GetSpaceWidth();

	void ResetVWFStatus();

	void Katakana2ARomajii(u32 letter, u32 unk1);

	void DrawLetter(u32 letter, u32 unk1);

	void TurnOffKatakana2Romaji();
}

#endif