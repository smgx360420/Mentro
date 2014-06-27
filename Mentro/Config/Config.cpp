#include "Config.h"

typedef struct{
public:
	u32 WAVE_A_TOP0;
	u32 WAVE_A_BOTTOM0;
	u32 WAVE_B_TOP0;
	u32 WAVE_B_BOTTOM0;

	u32 WAVE_A_TOP1;
	u32 WAVE_A_BOTTOM1;
	u32 WAVE_B_TOP1;
	u32 WAVE_B_BOTTOM1;

	u32 WAVE_A_TOP2;
	u32 WAVE_A_BOTTOM2;
	u32 WAVE_B_TOP2;
	u32 WAVE_B_BOTTOM2;

	u32 WAVE_A_TOP3;
	u32 WAVE_A_BOTTOM3;
	u32 WAVE_B_TOP3;
	u32 WAVE_B_BOTTOM3;

	u32 WAVE_A_TOP4;
	u32 WAVE_A_BOTTOM4;
	u32 WAVE_B_TOP4;
	u32 WAVE_B_BOTTOM4;

	u32 WAVE_A_TOP5;
	u32 WAVE_A_BOTTOM5;
	u32 WAVE_B_TOP5;
	u32 WAVE_B_BOTTOM5;

	u32 WAVE_A_TOP6;
	u32 WAVE_A_BOTTOM6;
	u32 WAVE_B_TOP6;
	u32 WAVE_B_BOTTOM6;

	u32 SELECTION_COL;
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
	Settings.WAVE_A_TOP0 = RGBA(255, 255, 255, 255);
	Settings.WAVE_A_TOP1 = RGBA(255, 0, 0, 255);
	Settings.WAVE_A_TOP2 = RGBA(0, 255, 0, 255);
	Settings.WAVE_A_TOP3 = RGBA(0, 0, 255, 255);
	Settings.WAVE_A_TOP4 = RGBA(255, 0, 0, 255);
	Settings.WAVE_A_TOP5 = RGBA(0, 255, 0, 255);
	Settings.WAVE_A_TOP6 = RGBA(0, 0, 255, 255);

	Settings.WAVE_A_BOTTOM0 = RGBA(255, 255, 255, 0);
	Settings.WAVE_A_BOTTOM1 = RGBA(255, 0, 0, 0);
	Settings.WAVE_A_BOTTOM2 = RGBA(0, 255, 0, 0);
	Settings.WAVE_A_BOTTOM3 = RGBA(0, 0, 255, 0);
	Settings.WAVE_A_BOTTOM4 = RGBA(255, 0, 0, 0);
	Settings.WAVE_A_BOTTOM5 = RGBA(0, 255, 0, 0);
	Settings.WAVE_A_BOTTOM6 = RGBA(0, 0, 255, 0);

	Settings.WAVE_B_TOP0 = RGBA(0, 0, 0, 255);
	Settings.WAVE_B_TOP6 = RGBA(255, 0, 0, 255);
	Settings.WAVE_B_TOP5 = RGBA(0, 255, 0, 255);
	Settings.WAVE_B_TOP4 = RGBA(0, 0, 255, 255);
	Settings.WAVE_B_TOP3 = RGBA(255, 0, 0, 255);
	Settings.WAVE_B_TOP2 = RGBA(0, 255, 0, 255);
	Settings.WAVE_B_TOP1 = RGBA(0, 0, 255, 255);

	Settings.WAVE_B_BOTTOM0 = RGBA(0, 0, 0, 0);
	Settings.WAVE_B_BOTTOM6 = RGBA(255, 0, 0, 0);
	Settings.WAVE_B_BOTTOM5 = RGBA(0, 255, 0, 0);
	Settings.WAVE_B_BOTTOM4 = RGBA(0, 0, 255, 0);
	Settings.WAVE_B_BOTTOM3 = RGBA(255, 0, 0, 0);
	Settings.WAVE_B_BOTTOM2 = RGBA(0, 255, 0, 0);
	Settings.WAVE_B_BOTTOM1 = RGBA(0, 0, 255, 0);

	//Settings.WAVE_B_TOP0 = RGBA(228, 69, 69, 100);
	//Settings.WAVE_B_BOTTOM0 = RGBA(255, 255, 255, 0);
	Settings.SELECTION_COL = RGBA(255, 255, 255, 255);
}

u32 Config::GetU32(Config::ConfigParams params)
{
	switch (params)
	{
	case Config::WAVE_A_BOTTOM0:
		return Settings.WAVE_A_BOTTOM0;
		break;
	case Config::WAVE_A_TOP0:
		return Settings.WAVE_A_TOP0;
		break;
	case Config::WAVE_B_BOTTOM0:
		return Settings.WAVE_B_BOTTOM0;
		break;
	case Config::WAVE_B_TOP0:
		return Settings.WAVE_B_TOP0;
		break;

	case Config::WAVE_A_BOTTOM1:
		return Settings.WAVE_A_BOTTOM1;
		break;
	case Config::WAVE_A_TOP1:
		return Settings.WAVE_A_TOP1;
		break;
	case Config::WAVE_B_BOTTOM1:
		return Settings.WAVE_B_BOTTOM1;
		break;
	case Config::WAVE_B_TOP1:
		return Settings.WAVE_B_TOP1;
		break;

	case Config::WAVE_A_BOTTOM2:
		return Settings.WAVE_A_BOTTOM2;
		break;
	case Config::WAVE_A_TOP2:
		return Settings.WAVE_A_TOP2;
		break;
	case Config::WAVE_B_BOTTOM2:
		return Settings.WAVE_B_BOTTOM2;
		break;
	case Config::WAVE_B_TOP2:
		return Settings.WAVE_B_TOP2;
		break;

	case Config::WAVE_A_BOTTOM3:
		return Settings.WAVE_A_BOTTOM3;
		break;
	case Config::WAVE_A_TOP3:
		return Settings.WAVE_A_TOP3;
		break;
	case Config::WAVE_B_BOTTOM3:
		return Settings.WAVE_B_BOTTOM3;
		break;
	case Config::WAVE_B_TOP3:
		return Settings.WAVE_B_TOP3;
		break;

	case Config::WAVE_A_BOTTOM4:
		return Settings.WAVE_A_BOTTOM4;
		break;
	case Config::WAVE_A_TOP4:
		return Settings.WAVE_A_TOP4;
		break;
	case Config::WAVE_B_BOTTOM4:
		return Settings.WAVE_B_BOTTOM4;
		break;
	case Config::WAVE_B_TOP4:
		return Settings.WAVE_B_TOP4;
		break;

	case Config::WAVE_A_BOTTOM5:
		return Settings.WAVE_A_BOTTOM5;
		break;
	case Config::WAVE_A_TOP5:
		return Settings.WAVE_A_TOP5;
		break;
	case Config::WAVE_B_BOTTOM5:
		return Settings.WAVE_B_BOTTOM5;
		break;
	case Config::WAVE_B_TOP5:
		return Settings.WAVE_B_TOP5;
		break;

	case Config::WAVE_A_BOTTOM6:
		return Settings.WAVE_A_BOTTOM6;
		break;
	case Config::WAVE_A_TOP6:
		return Settings.WAVE_A_TOP6;
		break;
	case Config::WAVE_B_BOTTOM6:
		return Settings.WAVE_B_BOTTOM6;
		break;
	case Config::WAVE_B_TOP6:
		return Settings.WAVE_B_TOP6;
		break;

	case Config::SELECTION_COL:
		return Settings.SELECTION_COL;
		break;
	}
}