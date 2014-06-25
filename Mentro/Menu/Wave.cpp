#include "Wave.h"

OSL_COLOR waveTopA, waveBottomA;
OSL_COLOR waveTopB, waveBottomB;
u16 waveProgression;

void Wave::Render()
{
	for (int x = 0; x <= 480; x++)
	{
		int y = 30 * oslSin(waveProgression/4 + x, 1) + 100;
		int y2 = 50 * oslSin(waveProgression / 2 + x/2, 1) + 100;

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

	waveTopB = col3;
	waveBottomB = col4;
}