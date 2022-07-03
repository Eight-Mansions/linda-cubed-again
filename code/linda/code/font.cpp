#include "font.h"

const u8 widths[] = {
	5,	//  	00
	5,	// !	01
	7,	// "	02
	10,	// #	03
	10,	// $	04
	13,	// %	05
	13,	// &	06
	5,	// '	07
	7,	// (	08
	7,	// )	09
	10,	// *	0A
	10,	// +	0B
	5,	// ,	0C
	6,	// -	0D
	8,	// .	0E
	5,	// /	0F
	10,	// 0	10
	8,	// 1	11
	9,	// 2	12
	11,	// 3	13
	10,	// 4	14
	10,	// 5	15
	10,	// 6	16
	10,	// 7	17
	10,	// 8	18
	10,	// 9	19
	5,	// :	1A
	5,	// ;	1B
	10,	// <	1C
	10,	// =	1D
	10,	// >	1E
	10,	// ?	1F
	12,	// @	20
	12,	// A	21
	11,	// B	22
	10,	// C	23
	12,	// D	24
	11,	// E	25
	11,	// F	26
	11,	// G	27
	14,	// H	28
	7,	// I	29
	10,	// J	2A
	12,	// K	2B
	11,	// L	2C
	17,	// M	2D
	12,	// N	2E
	12,	// O	2F
	11,	// P	30
	12,	// Q	31
	12,	// R	32
	10,	// S	33
	12,	// T	34
	11,	// U	35
	12,	// V	36
	17,	// W	37
	12,	// X	38
	12,	// Y	39
	10,	// Z	3A
	5,	// [	3B
	8,	// \	3C
	6,	// ]	3D
	9,	// ^	3E
	10,	// _	3F
	6,	// `	40
	10,	// a	41
	10,	// b	42
	10,	// c	43
	10,	// d	44
	9,	// e	45
	8,	// f	46
	10,	// g	47
	11,	// h	48
	6,	// i	49
	6,	// j	4A
	11,	// k	4B
	6,	// l	4C
	16,	// m	4D
	11,	// n	4E
	9,	// o	4F
	10,	// p	50
	9,	// q	51
	8,	// r	52
	9,	// s	53
	7,	// t	54
	11,	// u	55
	10,	// v	56
	14,	// w	57
	10,	// x	58
	11,	// y	59
	9,	// z	5A
	6,	// {	5B
	4,	// |	5C
	6,	// }	5D
	9,	// ~	5E
};


u32 GetLetterWidth(const u32 letter)
{
	if (letter >= 0x829F && letter <= 0x82FE)
	{
		u32 idx = letter - 0x829F;
		return widths[idx];
	}
	else
	{
		return 0x10;
	}
}

u32 GetSentenceWidth(const u16* text, const u16* end)
{
	int textWidth = 0;
	int length = end - text;
	curLetIdx = length;
	for (int i = 0; i < length; i++) // There is also a check for <$09> but not sure what that does... maybe breaks too?
	{
		u32 letter = (text[i] & 0xFF) << 8 | text[i] >> 8;
		if (letter == 0x5C6E) // Not sure if it starts after or before the \n...
		{
			textWidth = 0;
		}
		else
		{
			textWidth += GetLetterWidth(letter);
		}
	}
	return textWidth;
}

//int GetYForCentering(const char* text, u32 length)
//{
//	u32 textwidth = GetSentenceWidth(text, length);
//
//	return (int)((256 >> 1) - (textwidth >> 1)); // 256 is the width of text box texture
//}