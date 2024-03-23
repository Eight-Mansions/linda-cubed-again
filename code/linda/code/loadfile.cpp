#include "loadfile.h"

void LoadSubtitles(u_long* filepos)
{
	const char* filename = "SUBTITLE.DAT";
	u_long fileinfo = GetFileInfo(filename);
	if (fileinfo != 0)
	{
		LoadFile(*(int*)(fileinfo + 0x10), 0x801D3800, *(int*)(fileinfo + 0x14));
	}

	return;
}
