#include "MainSection.h"

OSL_IMAGE *recentApp = NULL;

//All updates must be relative to the 'world' coordinates supplied
void MainSection::Update(u32 xPos, u32 yPos){

}

//All renders must be relative to the 'world' coordinates supplied
void MainSection::Render(u32 xPos, u32 yPos){
	//oslDrawRect(xPos, yPos, xPos + 240, yPos + 272, RGBA(0, 255, 0, 255));
	oslDrawString(xPos + 20, yPos + 20, "Main Menu");

	//Show the current time
	pspTime time;
	sceRtcGetCurrentClockLocalTime(&time);
	char apm[3] = "AM";
	if (time.hour >= 12)apm[0] = 'P';
	oslDrawStringf(xPos + 380, yPos + 20, "%i:%i %s", time.hour % 12, time.minutes, apm);

	//Draw the recent app icon
	oslDrawImageSimpleXY(recentApp, xPos + 20, yPos + 40);

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
	recentApp = oslLoadImageFilePNG("LGDEF.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
}