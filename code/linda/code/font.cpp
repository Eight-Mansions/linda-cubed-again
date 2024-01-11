#include "font.h"

const char romaji[][3] = {
{'A', 0,0}, {'A',0,0}, {'I',0,0}, {'I',0,0}, {'U',0,0}, {'U',0,0}, {'E',0,0}, {'E',0,0}, {'O',0,0}, {'O',0,0}, /* 0x8340 - 0x8349*/
{'K', 'A', 0},	{'G', 'A', 0},	{'K', 'I', 0},	 {'G', 'I', 0},   {'K', 'U', 0},   {'G', 'U', 0},	{'K', 'E', 0}, {'G', 'E', 0}, {'K', 'O', 0}, {'G', 'O', 0}, /* 0x834A - 0x8353 */
{'S', 'A', 0},	{'Z', 'A', 0},	{'S', 'H', 'I'}, {'Z', 'H', 'I'}, {'S', 'U', 0},   {'Z', 'U', 0},   {'S', 'E', 0}, {'Z', 'E', 0}, {'S', 'O', 0}, {'Z', 'O', 0}, /* 0x8354 - 0x835D */
{'T', 'A', 0},	{'D', 'A', 0},	{'C', 'H', 'I'}, {'J', 'I', 0},   {'T', 'S', 'U'}, {'T', 'S', 'U'}, {'Z', 'U', 0}, {'T', 'E', 0}, {'D', 'E', 0}, {'T', 'O', 0}, {'D', 'O', 0}, /* 0x835E - 0x8368 */
{'N', 'A', 0},	{'N', 'I', 0},	{'N', 'U', 0},	 {'N', 'E', 0},	  {'N', 'O', 0}, /* 0x8369 - 0x836D */
{'H', 'A', 0},	{'B', 'A', 0},	{'P', 'A', 0},	 {'H', 'I', 0},	  {'B', 'I', 0},   {'P', 'I', 0},	{'H', 'U', 0}, {'B', 'U', 0}, {'P', 'U', 0}, {'H', 'E', 0}, {'B', 'E', 0}, {'P', 'E', 0}, {'H', 'O', 0}, {'B', 'O', 0}, {'P', 'O', 0}, /* 0x836E - 0x837C */
{'M', 'A', 0},	{'M', 'I', 0},  {0,0,0},         {'M', 'U', 0},   {'M', 'E', 0},   {'M', 'O', 0}, /* 0x837D - 0x8382 */
{'Y', 'A', 0},	{'Y', 'A', 0},	{'Y', 'U', 0},	 {'Y', 'U', 0},	  {'Y', 'O', 0},   {'Y', 'O', 0}, /* 0x8383 - 0x8388 */
{'R', 'A', 0},	{'R', 'I', 0},	{'R', 'U', 0},	 {'R', 'E', 0},	  {'R', 'O', 0},  /* 0x8389 - 0x838D */
{'W', 'A', 0},	{'W', 'A', 0},	{'W', 'I', 0},	 {'W', 'E', 0},	  {'W', 'O', 0},   {'N', 0, 0} }; /* 0x838E - 0x8393 */

const u8 widths[] = {
	0x04, //  
	0x02, // !
	0x04, // "
	0x08, // #
	0x06, // $
	0x07, // %
	0x06, // &
	0x02, // '
	0x04, // (
	0x04, // )
	0x04, // *
	0x06, // +
	0x03, // ,
	0x06, // -
	0x02, // .
	0x05, // /
	0x05, // 0
	0x04, // 1
	0x05, // 2
	0x05, // 3
	0x05, // 4
	0x06, // 5
	0x05, // 6
	0x05, // 7
	0x05, // 8
	0x05, // 9
	0x02, // :
	0x03, // ;
	0x07, // <
	0x06, // =
	0x07, // >
	0x06, // ?
	0x08, // @
	0x05, // A
	0x05, // B
	0x05, // C
	0x05, // D
	0x05, // E
	0x05, // F
	0x05, // G
	0x06, // H
	0x04, // I
	0x05, // J
	0x06, // K
	0x05, // L
	0x06, // M
	0x06, // N
	0x05, // O
	0x05, // P
	0x05, // Q
	0x05, // R
	0x05, // S
	0x06, // T
	0x06, // U
	0x06, // V
	0x06, // W
	0x06, // X
	0x06, // Y
	0x06, // Z
	0x05, // [
	0x10, // /	
	0x05, // ]
	0x08, // ^
	0x07, // _
	0x0C, // `
	0x05, // a
	0x05, // b 
	0x05, // c
	0x05, // d
	0x05, // e
	0x04, // f
	0x05, // g
	0x05, // h
	0x02, // i
	0x03, // j
	0x05, // k
	0x02, // l
	0x06, // m
	0x05, // n
	0x05, // o
	0x05, // p
	0x05, // q
	0x05, // r
	0x05, // s
	0x04, // t
	0x05, // u
	0x05, // v
	0x06, // w
	0x06, // x
	0x05, // y
	0x05, // z
	0x04, // {
	0x02, // |
	0x04, // }
	0x08, // ~
};

const u8 babyWidths[] = {
	0x04, //  
	0x02, // !
	0x04, // "
	0x09, // #
	0x06, // $
	0x07, // %
	0x06, // &
	0x02, // '
	0x04, // (
	0x04, // )
	0x04, // *
	0x06, // +
	0x03, // ,
	0x06, // -
	0x02, // .
	0x05, // /
	0x06, // 0
	0x04, // 1
	0x06, // 2
	0x06, // 3
	0x06, // 4
	0x06, // 5
	0x06, // 6
	0x06, // 7
	0x06, // 8
	0x06, // 9
	0x02, // :
	0x03, // ;
	0x07, // <
	0x06, // =
	0x07, // >
	0x06, // ?
	0x08, // @
	0x06, // A
	0x06, // B
	0x06, // C
	0x06, // D
	0x05, // E
	0x05, // F
	0x07, // G
	0x06, // H
	0x04, // I
	0x07, // J
	0x06, // K
	0x05, // L
	0x07, // M
	0x06, // N
	0x06, // O
	0x06, // P
	0x06, // Q
	0x06, // R
	0x06, // S
	0x06, // T
	0x06, // U
	0x06, // V
	0x08, // W
	0x06, // X
	0x06, // Y
	0x06ssss, // Z
	0x04, // [
	0x08, // /
	0x04, // ]
	0x08, // ^
	0x07, // _
	0x00, // `
	0x06, // a
	0x05, // b
	0x05, // c
	0x06, // d
	0x05, // e
	0x06, // f
	0x05, // g
	0x05, // h
	0x02, // i
	0x05, // j
	0x05, // k
	0x02, // l
	0x08, // m
	0x05, // n
	0x05, // o
	0x05, // p
	0x06, // q
	0x05, // r
	0x05, // s
	0x04, // t
	0x06, // u
	0x06, // v
	0x08, // w
	0x06, // x
	0x06, // y
	0x05, // z
	0x04, // {
	0x02, // |
	0x04, // }
	0x08, // ~
	0x08, // 5F
};

u8 GetLetterWidth(const u8 letterWidths[], u8 defaultWidth)
{
	if (currentLetter == '`')
	{
		vwfOn = !vwfOn;
		return 0;
	}

	if (vwfOn)
	{
		if (currentLetter >= 0x20 && currentLetter <= 0x7F)
		{
			u32 idx = currentLetter - 0x20;
			return letterWidths[idx];
		}
		else if (currentLetter == 0x8145) // Space
		{
			return 0x03;
		}
		else if (currentLetter == 0x8161)
		{
			return 0x04;
		}
		else if (currentLetter >= 0x824F && currentLetter <= 0x8258) // SJIS 0 - 9
		{
			u32 idx = currentLetter - 0x821F;
			return letterWidths[idx];
		}
		else
		{
			return defaultWidth;
		}
	}
	
	return defaultWidth;
}

void SetLetter(const u32 letter)
{
	currentLetter = letter;
}

u16 GetRegularLetterWidth(u16 defaultWidth)
{
	return GetLetterWidth(widths, defaultWidth);
}

u16 GetBabyLetterWidth(u16 defaultWidth)
{
	return GetLetterWidth(babyWidths, defaultWidth);
}

u16 GetSpaceWidth()
{
	if (vwfOn)
	{
		return 4; // Yes I shouldn't hard code it but 4 is what I use...
	}
	else
	{
		return 8; // The only "special" ones are 8 wide.
	}
}

void ResetVWFStatus()
{
	vwfOn = true;
	return;
}

void TurnOffKatakana2Romaji()
{
	kana2romajiOn = false;
}

void TurnOnKatakana2Romaji()
{
	kana2romajiOn = true;
}

void Katakana2ARomajii(u32 letter, u32 unk1)
{
	if (kana2romajiOn && (letter >= 0x8340 && letter <= 0x8394))
	{
		for (int i = 0; i < 3; i++)
		{
			const char aLetter = romaji[letter - 0x8340][i];
			if (aLetter == 0)
				break;

			currentLetter = aLetter;
			DrawLetter(aLetter + 0x821F, unk1);
		}
	}
	else
	{
		DrawLetter(letter, unk1);
	}
}