#include "MainSection.h"

OSL_IMAGE *recentApp = NULL;
char Name[256] = "No Recent App";
char ID[16] = "-";

//All updates must be relative to the 'world' coordinates supplied
void MainSection::Update(u32 xPos, u32 yPos){
}

//All renders must be relative to the 'world' coordinates supplied
void MainSection::Render(u32 xPos, u32 yPos){
	oslDrawString(xPos + 20, yPos + 20, "Main Menu");

	//Show the current time
	pspTime time;
	sceRtcGetCurrentClockLocalTime(&time);
	char apm[3] = "AM";
	if (time.hour >= 12)apm[0] = 'P';
	oslDrawStringf(xPos + 380, yPos + 20, "%i:%i %s", time.hour % 12, time.minutes, apm);

	//Draw the recent app icon
	oslDrawImageSimpleXY(recentApp, xPos + 20, yPos + 40);
	oslDrawStringf(xPos + 20, yPos + 180, Name);

	for (u8 c = 1; c < MAX_SECTIONS; c++){
		Section *sect = Menu::getSection(c);

		if (sect != NULL){
			oslDrawImageXY(sect->GetSplashIcon(), sect->GetSplashX(), sect->GetSplashY());
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

	if (FileManager::FileExists("ms0:/TMP/PARAM.SFO")){
		SFOParse sfo;
		sfo.Parse("ms0:/TMP/PARAM.SFO");
		strcpy(Name, sfo.GetName());
		strcpy(ID, sfo.GetID());
	}
}