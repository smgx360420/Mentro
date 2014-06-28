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
	if (frames == 0)
	{
		sections[newSectId]->LoadResources();
	}
	if (frames < 480)
	{
		//Slide transition while not crossed the entire screen
		frames++;
		Wave::Update();
		Wave::Render();
		sections[curSectId]->Update(frames, 0);
		sections[curSectId]->Render(frames, 0);

		sections[newSectId]->Update(480 - frames, 0);
		sections[newSectId]->Render(480 - frames, 0);

		return 1;
	}
	else{
		frames = 0;
		//Apply the update and resume normal functions
		sections[curSectId]->UnloadResources();
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

OSL_FONT *mainFont, *jp;

void Menu::SelectFont(char *str)
{
	if (strchr(str, 0xE3) != NULL){
		oslSetFont(jp);
	}
	else{
		oslSetFont(mainFont);
	}
}

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
	//oslSetFramerate(60);
	//oslSetFrameskip(1);

	pspDebugScreenPrintf("Initialized OSLib...");

	u32 shudSkip = 0;


	OSL_IMAGE *wall = oslLoadImageFilePNG("WALL.PNG", OSL_IN_VRAM, OSL_PF_8888);

	mainFont = oslLoadIntraFontFile("FNTLT.PGF", INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);
	jp = oslLoadIntraFontFile("flash0:/font/jpn0.pgf", INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8);

	oslIntraFontSetStyle(mainFont, 0.8f, RGB(255, 255, 255), RGB(30, 30, 30), 0);
	oslIntraFontSetStyle(jp, 0.6f, RGB(255, 255, 255), RGB(30, 30, 30), 0);
	oslSetFont(mainFont);

	PBPParse::setDefaultUNKN();

	pspDebugScreenPrintf("Resources Loaded...");

	oslStartDrawing();
	oslClearScreen(RGB(0, 0, 0));

	Wave::Init();

	sections[0]->LoadResources();


	//Menu Loop
	while (!ShouldExit)
	{
		if (!shudSkip){

			oslStartDrawing();

			oslDrawImageSimpleXY(wall, 0, 0);

			//If an update is pending, transition
			if (updatePending)
			{
				updatePending = TransitionEffect();
			}
			else{

				oslReadKeys();

				Wave::Update();
				if (sectId > curSectId)sections[curSectId]->Update(0, 0);

				Wave::Render();
				if (sectId > curSectId)sections[curSectId]->Render(0, 0);


				if (osl_keys->pressed.L && osl_keys->pressed.R)
				{
					oslWriteImageFilePNG(oslGetDrawBuffer(), "ms0:/PICTURE/SCREENSHOT.PNG", 0);
				}
			}

			oslEndDrawing();

		}

		oslEndFrame();
		shudSkip = oslSyncFrame();
	}

	//Free Resources
	sections[curSectId]->UnloadResources();

	return toLaunchPath;
}
