#include "GameSelector.h"

OSL_IMAGE *splash = NULL;
PBPParse eboots[MAX_GAMEENTRIES];
int curEbootEntryNum = 0;

void GameSelector::LoadResources()
{
	//Find all installed apps and get their data
	FileManager::OpenDir("ms0:/PSP/GAME");
	while (FileManager::Next())
	{
		char path[400] = "ms0:/PSP/GAME/";

		if (FileManager::IsNextDir())
		{
			strcat(path, FileManager::GetNextFileName());
			FileManager::ChangeDir(path);
			if (FileManager::FileExists("EBOOT.PBP"))
			{
				eboots[curEbootEntryNum].Parse("EBOOT.PBP");
				curEbootEntryNum++;
			}
			else if (FileManager::FileExists("VBOOT.PBP"))
			{
				eboots[curEbootEntryNum].Parse("VBOOT.PBP");
				curEbootEntryNum++;
			}
			else if (FileManager::FileExists("FBOOT.PBP"))
			{
				eboots[curEbootEntryNum].Parse("FBOOT.PBP");
				curEbootEntryNum++;
			}
			else if (FileManager::FileExists("PBOOT.PBP"))
			{
				eboots[curEbootEntryNum].Parse("PBOOT.PBP");
				curEbootEntryNum++;
			}
			else if (FileManager::FileExists("wmenu.bin"))
			{
				eboots[curEbootEntryNum].Parse("wmenu.bin");
				curEbootEntryNum++;
			}
		}

	}
}

OSL_IMAGE* GameSelector::GetSplashIcon(){
	if (splash == NULL)splash = oslLoadImageFilePNG("GAME.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_5650);
	return splash;
	//return eboots[0].icon;
}

int GameSelector::GetSplashX()
{
	return 153;
}

int GameSelector::GetSplashY()
{
	return 40;
}

void GameSelector::Render(u32 xPos, u32 yPos)
{

}



void GameSelector::Update(u32 xPos, u32 yPos)
{

}

void GameSelector::UnloadResources()
{
}
