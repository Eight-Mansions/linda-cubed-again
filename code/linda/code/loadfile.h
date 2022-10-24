
#ifndef LOADFILE_H_
#define LOADFILE_H_

#include "platform.h"

extern "C" {
	extern u_long GetFileInfo(const char* filename);
	extern void LoadFile(u_long unk1, u_long filepos, u_long unk2);
	void LoadSubtitles(u_long* filepos);
}

#endif