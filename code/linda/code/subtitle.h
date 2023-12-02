#ifndef SUBTITLE_H_
#define SUBTITLE_H_

#include <string.h>
#include "platform.h"
#include "generated.h"

extern "C" {
	void InitVoiceSubtitle(const char* audioname);

	void InitMovieSubtitle(const char* videoname);

	void ResetMovieSubtitle();

	void DrawMovieSubtitle(RECT* area, u8* image, u8* font, u32 curFrame);

	extern int LoadImage(RECT* rect, u_long* p);
	
	extern uint32_t LoadSpriteToVRAM();

	extern void DisplaySprite(uint32_t action);
	
	extern void HideSprite(uint32_t someAddr, uint32_t command);

	static int movieSubIdx = -1;

	static int audioSubIdx = -1;

	extern void PlayVoice(u32 param1, u32 param2);

	void InitAudioSubtitle(u32 param1, u32 param2);

	void DrawAudioSubtitle();
}
#endif