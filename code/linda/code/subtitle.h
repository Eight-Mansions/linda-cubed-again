#ifndef SUBTITLE_H_
#define SUBTITLE_H_

#include <string.h>
#include "platform.h"
#include "generated.h"
#include "generated.h"

static subtitle_displayed currSub = {};

extern "C" {
	extern int DisplayFromGraphic16x16(int imgId, int unk1, int unk2, int unk3, int unk4, int unk5);

	extern int LoadTMS(const char* filename, int startIdx, int unk);
	
	void InitVoiceSubtitle(const char* audioname);

	void DrawAudioSubtitle();

	void InitMovieSubtitle(const char* videoname);

	void ResetMovieSubtitle();

	void DrawMovieSubtitle(RECT* area, u16* image, u16* font, u32 curFrame);

	extern int LoadImage(RECT* rect, u_long* p);

	static int movieSubIdx = -1;

	static int audioSubIdx = -1;
}
#endif