#include "font.h"

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

u32 GetLetterWidth(const u32 letter)
{
	if (letter >= 0x20 && letter <= 0x7F)
	{
		u32 idx = letter - 0x20;
		return widths[idx];
	}
	else if (letter == 0x8145)
	{
		return 0x03;
	}
	else if (letter >= 0x824F && letter <= 0x8258) // SJIS 0 - 9
	{
		u32 idx = letter - 0x821F;
		return widths[idx];
	}
	else
	{
		return 0x10;
	}
}

void UpdateLetterWidthForSmall()
{
	letterWidth = 0x08;
	return;
}

void SetLetterWidthNew(const u32 letter)
{
	if (letter == '`')
	{
		vwfOnOff = !vwfOnOff;
		letterWidth = 0;
		return;
	}

	if (letter >= 0x20 && letter <= 0x7F)
	{
		u32 idx = letter - 0x20;
		letterWidth = widths[idx];
	}
	else if (letter == 0x8145)
	{
		letterWidth = 0x03;
	}
	else if (letter >= 0x824F && letter <= 0x8258) // SJIS 0 - 9
	{
		u32 idx = letter - 0x821F;
		letterWidth = widths[idx];
	}
	else
	{
		letterWidth = 0x10;
	}
}

u16 GetLetterWidthNew(u16 defaultWidth)
{
	if (letterWidth == 0)
	{
		letterWidth = defaultWidth;
		return 0;
	}

	if (vwfOnOff)
	{
		return letterWidth;
	}
	else
	{
		return defaultWidth;
	}
}