#include "Wave.h"

OSL_COLOR waveTopA, waveBottomA, wTATrans, wBATrans;
OSL_COLOR waveTopB, waveBottomB, wTBTrans, wBBTrans;
u16 waveProgression;

void Wave::Render()
{
	for (int x = 0; x <= 480; x++)
	{
		int y = int(30 * oslSin(waveProgression/4 + x, 1) + 100 + .5);
		int y2 = int(50 * oslSin(waveProgression / 2 + x/2, 1) + 100 + .5);

		//oslDrawGradientRect(x, y2 - 40, x + 1, y2, waveBottomA, waveBottomA, waveTopA, waveTopA);
		oslDrawGradientRect(x, y2 - 1, x + 1, y2 + 100 - 1, wTATrans, wTATrans, wBATrans, wBATrans);

		//oslDrawGradientRect(x, y - 40 , x + 1, y, waveBottomB, waveBottomB, waveTopB, waveTopB);
		oslDrawGradientRect(x, y - 1, x + 1, y + 100 - 1, wTBTrans, wTBTrans, wBBTrans, wBBTrans);

		//oslDrawGradientRect(x, y2 - 40, x + 1, y2, waveBottomA, waveBottomA, waveTopA, waveTopA);
		oslDrawGradientRect(x, y2, x + 1, y2 + 100, waveTopA, waveTopA, waveBottomA, waveBottomA);

		//oslDrawGradientRect(x, y - 40 , x + 1, y, waveBottomB, waveBottomB, waveTopB, waveTopB);
		oslDrawGradientRect(x, y, x + 1, y + 100, waveTopB, waveTopB, waveBottomB, waveBottomB);
	}
}

void Wave::Update()
{
	waveProgression++;
	if (waveProgression >= 360 * 4)waveProgression = 0;
}

void Wave::Setup(u32 col1, u32 col2, u32 col3, u32 col4)
{
	waveTopA = col1;
	waveBottomA = col2;
	wTATrans = RGBA((waveTopA >> 24) & 0x000000FF, (waveTopA >> 16) & 0x000000FF, (waveTopA >> 8) & 0x000000FF, (waveTopA & 0x000000FF) /2);
	wBATrans = RGBA((waveBottomA >> 24) & 0x000000FF, (waveBottomA >> 16) & 0x000000FF, (waveBottomA >> 8) & 0x000000FF, (waveBottomA & 0x000000FF) /2);

	waveTopB = col3;
	waveBottomB = col4;
	wTBTrans = RGBA((waveTopB >> 24) & 0x000000FF, (waveTopB >> 16) & 0x000000FF, (waveTopB >> 8) & 0x000000FF, (waveTopB & 0x000000FF) /2);
	wBBTrans = RGBA((waveBottomB >> 24) & 0x000000FF, (waveBottomB >> 16) & 0x000000FF, (waveBottomB >> 8) & 0x000000FF, (waveBottomB & 0x000000FF) /2 );
}