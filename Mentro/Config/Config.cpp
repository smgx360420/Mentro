#include "Config.h"

typedef struct{
public:
	u32 WAVE_A_TOP;
	u32 WAVE_A_BOTTOM;
	u32 WAVE_B_TOP;
	u32 WAVE_B_BOTTOM;

} configSettings;

SceUID fid = NULL;
configSettings Settings;

int Config::LoadConfig()
{
	//Read write and create file if it doesn't exist
	fid = sceIoOpen("CONF.MEN", PSP_O_RDWR, 0777);
	if (fid >= 0)
	{
		SceOff size = sceIoLseek(fid, 0, PSP_SEEK_END);
		sceIoLseek(fid, 0, PSP_SEEK_SET);
		if (!sceIoRead(fid, &Settings, size))return -2;
	}
	else return -1;
}

int Config::SaveConfig()
{
	if (fid <= 0)
	{
		fid = sceIoOpen("CONF.MEN", PSP_O_WRONLY | PSP_O_CREAT, 0777);
	}

	sceIoLseek(fid, 0, PSP_SEEK_SET);
	if (!sceIoWrite(fid, &Settings, sizeof(configSettings)))return -2;
	else return -1;
}

int Config::CloseConfig()
{
	if (fid)
	{
		if (!sceIoClose(fid))return -2;
	}return -1;
}

int Config::LoadDefaultConfig()
{
	Settings.WAVE_A_TOP = RGBA(228, 69, 69, 100);
	Settings.WAVE_A_BOTTOM = RGBA(255, 255, 255, 0);
	Settings.WAVE_B_TOP = RGBA(228, 69, 69, 100);
	Settings.WAVE_B_BOTTOM = RGBA(255, 255, 255, 0);
}

u32 Config::GetU32(Config::ConfigParams params)
{
	switch (params)
	{
	case Config::WAVE_A_BOTTOM:
		return Settings.WAVE_A_BOTTOM;
		break;
	case Config::WAVE_A_TOP:
		return Settings.WAVE_A_TOP;
		break;
	case Config::WAVE_B_BOTTOM:
		return Settings.WAVE_B_BOTTOM;
		break;
	case Config::WAVE_B_TOP:
		return Settings.WAVE_B_TOP;
		break;
	}
}