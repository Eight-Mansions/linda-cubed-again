#include "subtitle.h"

int counter = 0;

int sdbmHash(const char* text) {
	int hash = 0;
	int i = 0;

	for (; text[i] != 0; i++) {
		hash = text[i] + (hash << 6) + (hash << 16) - hash;
	}
	return hash;
}

void InitSubtitle(const char* audioname, int idx)
{
	printf("name: %s - idx: %d", audioname, idx);
	int audionameHash = sdbmHash(audioname);
	for (int i = 0; i < subsCount; i++)
	{
		if (audionameHash == subs[i].id && idx == subs[i].idx)
		{
			counter = 0;
			currSub.parts = subs[i].parts;
			currSub.partsCount = subs[i].partsCount;
			currSub.nextPartIdx = 0;
			currSub.ticksTilNext = subs[i].parts[currSub.nextPartIdx].displayTime;
		}
	}
}

void DisplaySubtitle()
{
	
	if (currSub.parts != NULL)
	{
		printf("%d\n", counter++);
		currSub.ticksTilNext--;
		if (currSub.partsCount != 0 && currSub.ticksTilNext == 0)
		{
			for (int i = 0; i < currSub.parts[currSub.nextPartIdx].len; i++)
			{
				DisplayText(currSub.parts[currSub.nextPartIdx].text, i, 0, 0, 0);
			}

			currSub.nextPartIdx++;
			if (currSub.nextPartIdx < currSub.partsCount)
			{
				currSub.ticksTilNext = currSub.parts[currSub.nextPartIdx].displayTime;
			}
			else
			{
				currSub.partsCount = 0; // No parts left to show
			}
		}
	}
}

void ClearText()
{
	currSub.parts = NULL;
	DisplayText((const char*)0, 64, 1, 0, 0);
}