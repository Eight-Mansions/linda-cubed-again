#include "subtitle.h"

//This code is not needed at all but leaving it in here for reference if anyone wants to see a proper way to load files from CD :)
//while ((CdReadSync(1, 0)) > 0);

//const char* filename = "TEST.TIM";	
//u_long fileinfo = GetFileInfo(filename);

//u_int sector = *(u_int*)(fileinfo + 0x10);
//u_int size = *(u_int*)(fileinfo + 0x14);

//CdlLOC loc;
//CdIntToPos(sector, &loc);
//CdControl(CdlSetloc, (u_char*)&loc, 0);

//CdRead((size + 2047) / 2048, (u_long*)0x801DD000, CdlModeSpeed);
//while ((CdReadSync(1, 0)) > 0);

////if (fileinfo != 0)
////{
////	LoadFile(*(int*)(fileinfo + 0x10), filepos, *(int*)(fileinfo + 0x14));
////}
//
//TIM_IMAGE tim;
//GetTimInfo((uint32_t*)0x801DD000, &tim);
//RECT rect;
//setRECT(&rect, 512, 288, tim.prect->w, tim.prect->h);
//LoadImage(&rect, tim.paddr);

//u_char param[4];
//param[0] = 0xC8; // Not sure what combo of commands this is but its needed for audio...
//CdControl(CdlSetmode, param, 0);

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
int GetTimInfo(const uint32_t* tim, TIM_IMAGE* info) {

	if ((*(tim++) & 0xffff) != 0x0010)
		return 1;

	info->mode = *(tim++);
	if (info->mode & 8) {
		const uint32_t* palette_end = tim;
		palette_end += *(tim++) / 4;

		info->crect = (RECT*)tim;
		info->caddr = (u_long*)&tim[2];

		tim = palette_end;
	}
	else {
		info->caddr = 0;
	}

	tim++;
	info->prect = (RECT*)tim;
	info->paddr = (u_long*)&tim[2];

	return 0;
}
#define GetPtrULong(x)	*((u_long*)(x))

static u32 currentAudioFrame = 0;

void CanLoadAudioSubtitle(u32 mapId)
{
	if (mapId == 0xB2)
	{
		loadAudioSubtitle = false;
	}
	else
	{
		loadAudioSubtitle = true;
	}
}

void InitAudioSubtitle(u32 param1, u32 param2)
{
	if (loadAudioSubtitle)
	{
		for (int i = 0; i < audioSubtitlesCount; i++)
		{
			AudioSubtitle* subtitles = &audioSubtitles[i];
			if ((subtitles->id == param1 && subtitles->id2 == 0) || (subtitles->id == param1 && subtitles->id2 == param2))
			{
				audioSubIdx = i;
				int graphicId = subtitles->parts[0].graphicId;
				for (int j = 0; j < subtitles->partsCount; j++)
				{
					AudioSubtitlePart* part = &subtitles->parts[j];

					((uint32_t*)0x800b90fc)[0] = 2; // Multiplier
					((uint16_t*)0x800b8e94)[0] = part->x; // x
					((uint16_t*)0x800b8e9c)[0] = part->y; // y
					((uint16_t*)0x800b95d0)[0] = graphicId;
					part->generatedId = LoadSpriteToVRAM();

					((uint32_t*)0x800b90fc)[0] = 0; // Multiplier

					// Turn our graphic off (I would use the actual function but they hard coded the script position to pull the damn value)
					uint32_t flagPos = part->generatedId << 2;
					flagPos += 0x800c28d4;
					((uint32_t*)flagPos)[0] = 7;

					uint32_t layerPos = 0x800bc9f0 + part->generatedId;
					((u8*)layerPos)[0] = 20;

					uint32_t imageIdx = 0x801ee290 + (part->generatedId * 0x18);
					((u8*)imageIdx)[0] = j;

					currentAudioFrame = 0;
				}
			}
		}
	}

	PlayVoice(param1, param2);
}

void DrawAudioSubtitle()
{
	if (audioSubIdx >= 0)
	{
		for (int i = 0; i < audioSubtitles[audioSubIdx].partsCount; i++)
		{
			AudioSubtitlePart current = audioSubtitles[audioSubIdx].parts[i];
			if (current.startFrame <= currentAudioFrame && currentAudioFrame < current.endFrame)
			{
				uint32_t flagPos = current.generatedId << 2;
				flagPos += 0x800c28d4;
				((uint32_t*)flagPos)[0] = 0x06;
			}
			else
			{
				uint32_t flagPos = current.generatedId << 2;
				flagPos += 0x800c28d4;
				((uint32_t*)flagPos)[0] = 0x07;
			}

		}
		currentAudioFrame++;
	}
}

void ResetAudioSubtitle()
{
	if (audioSubIdx >= 0)
	{
		AudioSubtitle* subtitles = &audioSubtitles[audioSubIdx];
		for (int i = 0; i < subtitles->partsCount; i++)
		{			
			u32 generatedId = subtitles->parts[i].generatedId;
			RemoveSprite(generatedId, 0);

			((u8*)0x801ee290)[generatedId] = 0;
		}

		RemoveSprite2(subtitles->parts[0].graphicId, 0);

		audioSubIdx = -1;
	}
}

void InitMovieSubtitle(const char* videoname)
{
	if (letterPosition[1] == 0)								
	{
		int position = 0x180;
		for (int i = 1; i < 78; i++)
		{
			letterPosition[i] = position;
			position += 0x180;
		}
	}

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

void DrawMovieSubtitle(RECT* area, u8* image, u8* font, u32 curFrame)
{
	u32 sliceW = 16;
	u32 sliceWP = 16 * 3; // How many pixels wide are we?
	u32 sliceX = (area->x / 24) * 16;

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
					subs.parts[i].curY = subs.parts[i].y * 48;
				}

				u16 curX = (subs.parts[i].curX * 3);
				u16 curY = subs.parts[i].curY;
				while (subs.parts[i].textIdx < subs.parts[i].len)
				{
					u32 srcPixelPos = letterPosition[text[subs.parts[i].textIdx]];
					for (u32 x = 0; x < 8; x++)
					{
						for (u32 y = 0; y < 768;)
						{
							u32 imgPos = curX + curY + y;

							u8 sp = font[srcPixelPos++];
							if (sp != 0) image[imgPos] = sp;
							sp = font[srcPixelPos++];
							if (sp != 0) image[imgPos + 1] = sp;
							sp = font[srcPixelPos++];
							if (sp != 0) image[imgPos + 2] = sp;

							y += 48;
						}

						curX += 3;
					}

					subs.parts[i].textIdx++;

					if (curX >= sliceWP)
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