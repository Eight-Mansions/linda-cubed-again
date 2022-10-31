#include "subtitle.h"

const u8 widths[] =
{
		0x09, // A
		0x08, // B
		0x07, // C
		0x08, // D
		0x07, // E
		0x07, // F
		0x08, // G
		0x08, // H
		0x03, // I
		0x07, // J
		0x08, // K
		0x07, // L
		0x08, // M
		0x08, // N
		0x08, // O
		0x08, // P
		0x08, // Q
		0x08, // R
		0x07, // S
		0x08, // T
		0x07, // U
		0x08, // V
		0x09, // W
		0x07, // X
		0x07, // Y
		0x08, // Z
		0x07, // a
		0x07, // b
		0x07, // c
		0x07, // d
		0x07, // e
		0x05, // f
		0x07, // g
		0x07, // h
		0x03, // i
		0x04, // j
		0x07, // k
		0x04, // l
		0x07, // m
		0x07, // n
		0x07, // o
		0x07, // p
		0x07, // q
		0x06, // r
		0x07, // s
		0x05, // t
		0x07, // u
		0x07, // v
		0x07, // w
		0x07, // x
		0x07, // y
		0x07, // z
		0x04, // .
		0x04, // ,
		0x03, // !
		0x07, // ?
		0x06, // "
		0x04, // (
		0x05, // )
		0x04, // :
		0x04, // ;
		0x07, // ~
		0x03, // '
		0x06, // -
		0x07, // 0
		0x05, // 1
		0x08, // 2
		0x07, // 3
		0x08, // 4
		0x07, // 5
		0x07, // 6
		0x07, // 7
		0x08, // 8
		0x07, // 9
		0x04, //  
};

int counter = 0;
static int curAudioSubtitleLength = 0;

int sdbmHash(const char* text) {
	int hash = 0;
	int i = 0;

	for (; text[i] != 0; i++) {
		hash = text[i] + (hash << 6) + (hash << 16) - hash;
	}
	return hash;
}

//int GetLetterPos(u8 letter)
//{
//	int y = 0;
//	int x = 0;
//
//	letter -= 1;
//	y = (letter / 26);
//	x = letter - (y * 26);
//	y *= 16;
//	x *= 8;
//
//	return (y << 16 | x);
//}
//
//int yx = 0x0050005c;
//
//void InitVoiceSubtitle(const char* audioname)
//{
//	int audionameHash = sdbmHash(audioname);
//	for (int i = 0; i < subsCount; i++)
//	{
//		if (audionameHash == subs[i].id)
//		{
//			counter = 0;
//			curAudioSubtitleLength = 0;
//			currSub.parts = subs[i].parts;
//			currSub.partsCount = subs[i].partsCount;
//			currSub.nextPartIdx = 0;
//			currSub.ticksTilNext = subs[i].parts[currSub.nextPartIdx].displayTime;
//			yx = 0x0050005c;
//			break;
//		}
//	}
//}
//
//void DrawAudioSubtitle()
//{
//	if (currSub.partsCount != 0)
//	{
//		currSub.ticksTilNext--;
//		if (currSub.partsCount != 0 && currSub.ticksTilNext == 0)
//		{
//			if (curAudioSubtitleLength > 0)
//			{
//				u16 otagLength = *((u32*)0x800aa228);
//				otagLength -= curAudioSubtitleLength;
//				*((u32*)0x800aa228) = otagLength;
//			}
//
//			int uv = 0;
//			int wh = 0x00100008;
//
//			subtitle_part part = currSub.parts[currSub.nextPartIdx];
//			curAudioSubtitleLength = part.len;
//			yx = part.x | part.y << 0x10;
//			const char* text = part.text;
//
//			for (int i = 0; i < part.len; i++)
//			{
//				u8 letter = text[i];
//				if (letter != 0x7F)
//				{
//					uv = GetLetterPos(letter);
//					//DisplayFromGraphic16x16(0x0A, 0, yx, uv, wh, 0x19);
//					yx += 0x08;
//				}
//				else
//				{
//					i++;
//					yx = text[i] | (part.y + 16) << 0x10;
//					curAudioSubtitleLength -= 2;
//				}
//			}
//
//			currSub.nextPartIdx++;
//			if (currSub.nextPartIdx < currSub.partsCount)
//			{
//				currSub.ticksTilNext = currSub.parts[currSub.nextPartIdx].displayTime;
//			}
//			else
//			{
//				currSub.partsCount = 0; // No parts left to show
//			}
//		}
//
//		//UpdateOTAG(2);
//	}
//}

void InitMovieSubtitle(const char* videoname)
{
	movieSubIdx = -1;
	int videonameHash = sdbmHash(videoname);
	for (int i = 0; i < movieSubtitlesCount; i++)
	{
		if (videonameHash == movieSubtitles[i].id)
		{
			movieSubIdx = i;
			break;
		}
	}
}

void ResetMovieSubtitle()
{
	movieSubIdx = -1;
}

void DrawMovieSubtitle(RECT* area, u16* image, u8* font, u32 curFrame)
{
	u32 sliceW = area->w;
	u32 sliceX = area->x;

	if (movieSubIdx >= 0)
	{
		MovieSubtitle subs = movieSubtitles[movieSubIdx];

		for (int i = 0; i < subs.partsCount; i++)
		{

			if (subs.parts[i].startFrame <= curFrame && curFrame < subs.parts[i].endFrame)
			{
				const char* text = subs.parts[i].text;


				if (sliceX <= subs.parts[i].x && subs.parts[i].x < sliceX + sliceW)
				{
					subs.parts[i].textIdx = 0;
					subs.parts[i].curX = subs.parts[i].x - sliceX;
					subs.parts[i].curY = subs.parts[i].y * 24;
				}

				u16 curX = subs.parts[i].curX;
				u16 curY = subs.parts[i].curY;
				while (subs.parts[i].textIdx < subs.parts[i].len)
				{
					u32 srcPixelPos = text[subs.parts[i].textIdx] * 0x180; // 0x80 is half the width of our letters.  The entire byte count is (w * 2 (16bpp) * h).  We're using shorts or 2 bytes at a time so half.

					bool overflowed = false;
					for (u32 x = 0; x < 8; x++) // 8 is our max letter width... soon will be width of letter
					{
						for (u32 y = 0; y < 384;) // += 16 comes from max width of a character = 8 * 2 (16bpp = 2 bytes)  ----- 256 = may height times the 16 we get from the previous equation
						{
							u32 imgPos = curX + curY + y;

							// 0x8000 is the pixel color of the black background
							u8 sp = font[srcPixelPos++];
							if (sp != 0x8000) image[imgPos] = sp;
							sp = font[srcPixelPos++];
							if (sp != 0x8000) image[imgPos] = sp;
							sp = font[srcPixelPos++];
							if (sp != 0x8000) image[imgPos] = sp;

							//sp = font[srcPixelPos++];
							//if (sp != 0x8000) image[imgPos + 16] = sp;

							y += 24;
						}

						curX++;
					}

					subs.parts[i].textIdx++;

					if (curX >= sliceW)
					{
						subs.parts[i].curX = 0;
						break;
					}
				}
			}
		}
	}

	LoadImage(area, (u_long*)image);
}