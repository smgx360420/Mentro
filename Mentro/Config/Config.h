#pragma once
#include <pspkernel.h>
#include <oslib\oslib.h>

class Config
{
public:
	typedef enum{
		WAVE_A_TOP0 = 0,
		WAVE_A_BOTTOM0,
		WAVE_B_TOP0,
		WAVE_B_BOTTOM0,

		WAVE_A_TOP1,
		WAVE_A_BOTTOM1,
		WAVE_B_TOP1,
		WAVE_B_BOTTOM1,

		WAVE_A_TOP2,
		WAVE_A_BOTTOM2,
		WAVE_B_TOP2,
		WAVE_B_BOTTOM2,

		WAVE_A_TOP3,
		WAVE_A_BOTTOM3,
		WAVE_B_TOP3,
		WAVE_B_BOTTOM3,

		WAVE_A_TOP4,
		WAVE_A_BOTTOM4,
		WAVE_B_TOP4,
		WAVE_B_BOTTOM4,

		WAVE_A_TOP5,
		WAVE_A_BOTTOM5,
		WAVE_B_TOP5,
		WAVE_B_BOTTOM5,

		WAVE_A_TOP6,
		WAVE_A_BOTTOM6,
		WAVE_B_TOP6,
		WAVE_B_BOTTOM6,
		SELECTION_COL
	}ConfigParams;

	static int LoadConfig();
	static int LoadDefaultConfig();
	static int SaveConfig();
	static int CloseConfig();

	static u32 GetU32(ConfigParams params);
};

