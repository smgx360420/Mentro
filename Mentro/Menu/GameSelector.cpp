#include "GameSelector.h"

OSL_IMAGE *splash = NULL;
PBPParse eboots[MAX_GAMEENTRIES];
int curEbootEntryNum = 0;
float angleWidth = 0;
int selectedEntryID = 0;

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

	angleWidth = 180.0f / (float)(curEbootEntryNum - 1);
}

int getXPos(float angle, int length)
{
	return oslCosi(angle, length);
}

int getYPos(float angle, int length, int yPos)
{
	return yPos + oslSini(angle, length);
}

OSL_IMAGE* GameSelector::GetSplashIcon(){
	if (splash == NULL)splash = oslLoadImageFilePNG("GAME.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_5650);
	return splash;
	//return eboots[0].icon;
}

int GameSelector::GetSplashX()
{
	return 40;
}

int GameSelector::GetSplashY()
{
	return 40;
}

void GameSelector::Render(u32 xPos, u32 yPos)
{
	for (int c = 0; c < curEbootEntryNum; c++){
		if(eboots[c].icon != NULL)oslDrawImageSimpleXY(eboots[c].icon, xPos + getXPos(90 - angleWidth * c, 100), getYPos(90 - angleWidth * c, 100, 100));
	}

	if (eboots[selectedEntryID].icon != NULL)oslDrawImageSimpleXY(eboots[selectedEntryID].icon, xPos + getXPos(90 - angleWidth * selectedEntryID, 100), getYPos(90 - angleWidth * selectedEntryID, 100, 100));
	
	//Draw the border around the selected item
	oslDrawRect(xPos + getXPos(90 - angleWidth * selectedEntryID, 100), getYPos(90 - angleWidth * selectedEntryID, 100, 100), xPos + getXPos(90 - angleWidth * selectedEntryID, 100) + 64, getYPos(90 - angleWidth * selectedEntryID, 100, 100) + 64, Config::GetU32(Config::SELECTION_COL));

	oslDrawFillRect(xPos + 180, yPos + 120, xPos + 480, yPos + 200, RGB(0,0,0) );
	Menu::SelectFont(eboots[selectedEntryID].sfo.GetName());
	oslDrawString(xPos + 190, yPos + 150, eboots[selectedEntryID].sfo.GetName());
	Menu::SelectFont("LOL");

}



void GameSelector::Update(u32 xPos, u32 yPos)
{
	//Return to main menu
	if (osl_keys->pressed.circle)Menu::TransitionSection(0);

	if (osl_keys->pressed.up)selectedEntryID++;
	if (osl_keys->pressed.down)selectedEntryID--;

	if (selectedEntryID < 0)selectedEntryID = 0;
	if (selectedEntryID >= curEbootEntryNum)selectedEntryID = curEbootEntryNum - 1;
}

void GameSelector::UnloadResources()
{
}
