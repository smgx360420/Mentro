#include "Menu.h"

#pragma region
char *appPath, *toLaunchPath;
int toLaunchType, toLaunchExtra;

Section *sections[MAX_SECTIONS];
u8 sectId = 0;

u8 curSectId = 0;
u8 newSectId = 0;

u8 ShouldExit = 0;
u8 updatePending = 0;
#pragma endregion

void Menu::setAppPath(char *path)
{
	appPath = path;
	*(strrchr(appPath, '/') + 1) = 0x0;	//Terminate app path at last directory before eboot	
	//sceIoChdir(appPath);
}

void Menu::RegisterSection(Section *section)
{
	//Only register a section if a free slot is available
	if (sectId < MAX_SECTIONS){
		sections[sectId] = section;
		sectId++;
	}
}

void Menu::TransitionSection(u8 sectToTransition)
{
	newSectId = sectToTransition;
	updatePending = 1;	//The menu system needs to update its transition routines
}

Section* Menu::getSection(u8 id)
{
	if (id < sectId)
	return sections[id];
	else return NULL;
}

//Slide Transition effect 
u16 frames = 0;
u8 TransitionEffect()
{
	if (frames < 480)
	{
		//Slide transition while not crossed the entire screen
		frames++;
		sections[curSectId]->Render(frames, 0);
		sections[newSectId]->Render(480 - frames, 0);

		return 1;
	}
	else{
		frames = 0;
		//Apply the update and resume normal functions
		sections[curSectId]->UnloadResources();
		sections[newSectId]->LoadResources();
		curSectId = newSectId;
		newSectId = 0;
		return 0;
	}
}

#pragma region
void Menu::Launch(char* appPath, int appType, int appExtra)
{
	toLaunchPath = appPath;
	toLaunchType = appType;
	toLaunchExtra = appExtra;
	ShouldExit = 1;
}

int Menu::getAppType()
{
	return toLaunchType;
}

int Menu::getExtraInfo()
{
	return toLaunchExtra;
}
#pragma endregion

char* Menu::Start()
{
	//Load Resources
	oslInit(0);
	oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);
	oslInitGfx(OSL_PF_8888, 1);
	oslInitAudio();
	oslSetQuitOnLoadFailure(1);
	oslSetKeyAutorepeatInit(40);
	oslSetKeyAutorepeatInterval(10);

	pspDebugScreenPrintf("Initialized OSLib...");

	u32 shudSkip = 0;

	Wave::Setup(Config::GetU32(Config::WAVE_A_TOP), Config::GetU32(Config::WAVE_A_BOTTOM), Config::GetU32(Config::WAVE_B_TOP), Config::GetU32(Config::WAVE_B_BOTTOM));

	OSL_IMAGE *wall = oslLoadImageFilePNG("WALL.PNG", OSL_IN_VRAM, OSL_PF_8888);

	OSL_FONT *mainFont = oslLoadIntraFontFile("FNTLT.PGF", INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);
	oslIntraFontSetStyle(mainFont, 0.8f, RGB(255,255,255), RGB(30,30,30), 0);
	oslSetFont(mainFont);

	pspDebugScreenPrintf("Resources Loaded...");

	oslStartDrawing();
	oslClearScreen(RGB(0, 0, 0));

	sections[0]->LoadResources();

	//Enable bilinear filtering
	//oslSetBilinearFilter(1);

	//Menu Loop
	while (!ShouldExit)
	{
		if (shudSkip)goto needToSkip;

		oslStartDrawing();

		oslDrawImageSimpleXY(wall, 0, 0);

		//If an update is pending, transition
		if (updatePending)
		{
			updatePending = TransitionEffect();
		}
		else{
			Wave::Update();
			if(sectId > curSectId)sections[curSectId]->Update(0, 0);

			Wave::Render();
			if(sectId > curSectId)sections[curSectId]->Render(0, 0);
		}

		oslEndDrawing();

	needToSkip:
		shudSkip = oslSyncFrame();
	}

	//Free Resources
	sections[curSectId]->UnloadResources();

	return toLaunchPath;
}
