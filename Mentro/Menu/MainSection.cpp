#include "MainSection.h"

OSL_IMAGE *recentApp = NULL, *recentPic1;
char Name[256] = "No Recent App";
char ID[16] = "-";
int selectedID = 0;

//All updates must be relative to the 'world' coordinates supplied
void MainSection::Update(u32 xPos, u32 yPos){
	if (osl_keys->pressed.left)
	{
		selectedID--;
	}
	else if (osl_keys->pressed.right)
	{
		selectedID++;
	}

	if (selectedID < 0)selectedID = 0;
	if (selectedID >= MAX_SECTIONS)selectedID = MAX_SECTIONS - 1;
}

void drawRect(int x, int y, int width, int height)
{
	oslDrawRect(x, y, x + width, y + height, Config::GetU32(Config::SELECTION_COL));
}

void drawRecent(int xPos, int yPos)
{
	//Draw the recent app icon
	if (recentPic1 != NULL)oslDrawImageSimpleXY(recentPic1, xPos + 20, yPos + 40);
	oslDrawImageSimpleXY(recentApp, xPos + 20, yPos + 40);

	//Autoselect the language
	Menu::SelectFont(Name);
	oslDrawStringf(xPos + 20, yPos + 188, Name);

	//Reset the font  :P
	Menu::SelectFont("LOL");


	if (selectedID == 0)
	{
		drawRect(xPos + 20, yPos + 40, 128, 128);
	}
}

void drawTime(int xPos, int yPos)
{
	//Show the current time
	pspTime time;
	sceRtcGetCurrentClockLocalTime(&time);
	char apm[3] = "AM";
	if (time.hour >= 12)apm[0] = 'P';
	oslDrawStringf(xPos + 380, yPos + 20, "%02i:%02i %s", time.hour % 12, time.minutes, apm);
}

//All renders must be relative to the 'world' coordinates supplied
void MainSection::Render(u32 xPos, u32 yPos){
	oslDrawString(xPos + 20, yPos + 20, "Main Menu");

	drawTime(xPos, yPos);
	drawRecent(xPos, yPos);
	

	for (u8 c = 1; c < MAX_SECTIONS; c++){
		Section *sect = Menu::getSection(c);

		if (sect != NULL){
			oslDrawImageXY(sect->GetSplashIcon(), xPos + sect->GetSplashX() + 128, sect->GetSplashY() + yPos);
			if (c == selectedID)
				drawRect(xPos + 128 + sect->GetSplashX(), yPos + sect->GetSplashY(), oslGetImageWidth(sect->GetSplashIcon()), oslGetImageHeight(sect->GetSplashIcon()));
			if (c == selectedID && osl_keys->pressed.cross)
			{
				Menu::TransitionSection(c);
			}
		}
		else{
			break;
		}
	}
}

OSL_IMAGE* MainSection::GetSplashIcon(){

}

void MainSection::UnloadResources(){
	oslDeleteImage(recentApp);
}

void MainSection::LoadResources(){
	//Load the most recent app icon to show
	if (FileManager::FileExists("ms0:/TMP/ICON0.PNG")) recentApp = oslLoadImageFilePNG("ms0:/TMP/ICON0.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	else recentApp = oslLoadImageFilePNG("LGDEF.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

	//Load the most recent app icon to show
	if (FileManager::FileExists("ms0:/TMP/PIC1SC.PNG")) recentPic1 = oslLoadImageFilePNG("ms0:/TMP/PIC1SC.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	else recentPic1 = NULL;

	if (FileManager::FileExists("ms0:/TMP/PARAM.SFO")){
		SFOParse sfo;
		sfo.Parse("ms0:/TMP/PARAM.SFO");
		strcpy(Name, sfo.GetName());
		strcpy(ID, sfo.GetID());
	}
}