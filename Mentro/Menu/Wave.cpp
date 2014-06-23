#include "Wave.h"

OSL_COLOR waveTop, waveBottom;
u16 waveProgression;

void Wave::Render()
{
	for (int x = 0; x <= 480; x+=2)
	{
		int y = 30 * oslSin(waveProgression/4 + x, 1) + 100;
		int y2 = 50 * oslSin(waveProgression / 2 + x, 1) + 100;

		oslDrawGradientRect(x, 0, x + 2, y2, waveBottom, waveBottom, waveTop, waveTop);
		oslDrawGradientRect(x, y2, x + 2, 272, waveTop, waveTop, waveBottom, waveBottom);

		oslDrawGradientRect(x, 0 , x + 2, y, waveBottom, waveBottom, waveTop, waveTop);
		oslDrawGradientRect(x, y, x + 2, 272, waveTop, waveTop, waveBottom, waveBottom);
	}
}

void Wave::Update()
{
	waveProgression++;
	if (waveProgression >= 360 * 4)waveProgression = 0;
}

void Wave::Setup(u32 col1, u32 col2)
{
	waveTop = col1;
	waveBottom = col2;
}