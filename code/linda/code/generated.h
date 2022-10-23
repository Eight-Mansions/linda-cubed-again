#ifndef GENERATED_H_
#define GENERATED_H_

#include "platform.h"

struct subtitle_part {
	const char* text;
	const u8 len;
	const u16 displayTime;
	const u8 x;
	const u8 y;
};
struct subtitle {
	const i32 id;
	const u8 partsCount;
	const subtitle_part* parts;
};
struct subtitle_displayed {
	const subtitle_part* parts;
	u8 partsCount;
	u8 nextPartIdx;
	u8 ticksTilNext;
};

extern const u32 subsCount;
extern const subtitle subs[];

struct MovieSubtitlePart {
	const char* text;
	const u8 len;
	u8 textIdx;
	const u16 startFrame;
	const u16 endFrame;
	const u16 x;
	const u16 y;
	const u16 w;
	u16 curX;
	u16 curY;
};

struct MovieSubtitle {
	const i32 id;
	const u8 partsCount;
	MovieSubtitlePart* parts;
};

extern const u32 movieSubtitlesCount;
extern MovieSubtitle movieSubtitles[];
#endif