#pragma once
#include <pspkernel.h>
#include <oslib\oslib.h>

class Config
{
public:
	typedef enum{
		WAVE_A_TOP = 0,
		WAVE_A_BOTTOM,
		WAVE_B_TOP,
		WAVE_B_BOTTOM,
		SELECTION_COL
	}ConfigParams;

	static int LoadConfig();
	static int LoadDefaultConfig();
	static int SaveConfig();
	static int CloseConfig();

	static u32 GetU32(ConfigParams params);
};

