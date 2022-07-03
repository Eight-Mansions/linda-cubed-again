#ifndef TEXT_H_
#define TEXT_H_

#include "platform.h"

extern "C" {
	extern u32 curLetIdx;

	void ConvertTextToTwoBytes(u8* src, int srcIdx, u8* dest);

	void SetVRAMUploadXY(u16* xpos, u16* ypos);

	void SetLetSrcXY(u8* xy);
}

#endif