#include "Wave.h"

OSL_COLOR waveTopA, waveBottomA, wTANxt, wBANxt, wTATrans, wBATrans;
OSL_COLOR waveTopB, waveBottomB, wTBNxt, wBBNxt, wTBTrans, wBBTrans;
u16 waveProgression;
float progress = 0.0f;


u8 INTERPOLATE_BYTE(u8 ac, u8 bc, float x)
{
	float a = ac;
	float b = bc;

	int answer = (int)( ((1.0f - x) * a) + (x * b) );

	return (u8)answer;
}

u32 interpolate(u32 colA, u32 colB, float x)
{
	u8 colAR = colA & 0x000000ff;
	u8 colAG = (colA & 0x0000ff00) >> 8;
	u8 colAB = (colA & 0x00ff0000) >> 16;
	u8 colAA = (colA & 0xff000000) >> 24;

	u8 colBR = colB & 0x000000ff;
	u8 colBG = (colB & 0x0000ff00) >> 8;
	u8 colBB = (colB & 0x00ff0000) >> 16;
	u8 colBA = (colB & 0xff000000) >> 24;

	return RGBA(INTERPOLATE_BYTE(colAR, colBR, x), INTERPOLATE_BYTE(colAG, colBG, x), INTERPOLATE_BYTE(colAB, colBB, x), INTERPOLATE_BYTE(colAA, colBA, x));
}

void Wave::Init()
{
	waveTopA = Config::GetU32(Config::WAVE_A_TOP0);
	waveTopB = Config::GetU32(Config::WAVE_B_TOP0);
	waveBottomA = Config::GetU32(Config::WAVE_A_BOTTOM0);
	waveBottomB = Config::GetU32(Config::WAVE_B_BOTTOM0);

	wTANxt = Config::GetU32(Config::WAVE_A_TOP1);
	wTBNxt = Config::GetU32(Config::WAVE_B_TOP1);
	wBANxt = Config::GetU32(Config::WAVE_A_BOTTOM1);
	wBBNxt = Config::GetU32(Config::WAVE_B_BOTTOM1);
}

void Wave::Render()
{
	oslSetBilinearFilter(1);
	for (int x = 0; x <= 480; x+=2)
	{
		int y = int(30 * oslSin(waveProgression/4 + x, 1) + 100 + .5);
		int y2 = int(50 * oslSin(waveProgression / 2 + x/2, 1) + 100 + .5);

		oslDrawGradientRect(x, y2, x + 2, y2 + 100, waveTopA, waveTopA, waveBottomA, waveBottomA);
		oslDrawGradientRect(x, y, x + 2, y + 100, waveTopB, waveTopB, waveBottomB, waveBottomB);
	}
	oslSetBilinearFilter(0);
}

void Wave::Update()
{
	waveProgression++;
	if (waveProgression >= 360 * 4)waveProgression = 0;
	progress += 0.00392156862f;
	//progress += 0.1f;

	waveTopA = interpolate(waveTopA, wTANxt, progress);
	waveTopB = interpolate(waveTopB, wTBNxt, progress);
	waveBottomA = interpolate(waveBottomA, wBANxt, progress);
	waveBottomB = interpolate(waveBottomB, wBBNxt, progress);

	if (progress >= 1)
	{
		progress = 0;
		if (wTANxt == Config::GetU32(Config::WAVE_A_TOP1))
		{
			wTANxt = Config::GetU32(Config::WAVE_A_TOP2);
			wTBNxt = Config::GetU32(Config::WAVE_B_TOP2);
			wBANxt = Config::GetU32(Config::WAVE_A_BOTTOM2);
			wBBNxt = Config::GetU32(Config::WAVE_B_BOTTOM2);
		}
		else if (wTANxt == Config::GetU32(Config::WAVE_A_TOP2))
		{
			wTANxt = Config::GetU32(Config::WAVE_A_TOP3);
			wTBNxt = Config::GetU32(Config::WAVE_B_TOP3);
			wBANxt = Config::GetU32(Config::WAVE_A_BOTTOM3);
			wBBNxt = Config::GetU32(Config::WAVE_B_BOTTOM3);
		}
		else if (wTANxt == Config::GetU32(Config::WAVE_A_TOP3))
		{
			wTANxt = Config::GetU32(Config::WAVE_A_TOP4);
			wTBNxt = Config::GetU32(Config::WAVE_B_TOP4);
			wBANxt = Config::GetU32(Config::WAVE_A_BOTTOM4);
			wBBNxt = Config::GetU32(Config::WAVE_B_BOTTOM4);
		}
		else if (wTANxt == Config::GetU32(Config::WAVE_A_TOP4))
		{
			wTANxt = Config::GetU32(Config::WAVE_A_TOP5);
			wTBNxt = Config::GetU32(Config::WAVE_B_TOP5);
			wBANxt = Config::GetU32(Config::WAVE_A_BOTTOM5);
			wBBNxt = Config::GetU32(Config::WAVE_B_BOTTOM5);
		}
		else if (wTANxt == Config::GetU32(Config::WAVE_A_TOP5))
		{
			wTANxt = Config::GetU32(Config::WAVE_A_TOP6);
			wTBNxt = Config::GetU32(Config::WAVE_B_TOP6);
			wBANxt = Config::GetU32(Config::WAVE_A_BOTTOM6);
			wBBNxt = Config::GetU32(Config::WAVE_B_BOTTOM6);
		}
		else if (wTANxt == Config::GetU32(Config::WAVE_A_TOP6))
		{
			wTANxt = Config::GetU32(Config::WAVE_A_TOP0);
			wTBNxt = Config::GetU32(Config::WAVE_B_TOP0);
			wBANxt = Config::GetU32(Config::WAVE_A_BOTTOM0);
			wBBNxt = Config::GetU32(Config::WAVE_B_BOTTOM0);
		}
	}
}
