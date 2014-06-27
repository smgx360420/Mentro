#pragma once
#include <string.h>
#include <pspsdk.h>
#include "Section.h"
#include "../Common.h"
#include "../Config/Config.h"
#include "Wave.h"
#include <stdlib.h>

class Menu
{
public:
	static void setAppPath(char *path);
	static void RegisterSection(Section *section);
	static char* Start();
	static int getAppType();
	static int getExtraInfo();
	static Section* getSection(u8 id);
	static void SelectFont(char* str);

	static void TransitionSection(u8 sectToTranstion);
	static void Launch(char* appPath, int appType, int appExtra);
};
