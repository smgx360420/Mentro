#include "MainSection.h"

//All updates must be relative to the 'world' coordinates supplied
void MainSection::Update(u32 xPos, u32 yPos){

}

//All renders must be relative to the 'world' coordinates supplied
void MainSection::Render(u32 xPos, u32 yPos){
	//oslDrawRect(xPos, yPos, xPos + 240, yPos + 272, RGBA(0, 255, 0, 255));
	oslDrawString(xPos + 20, yPos + 20, "Main Menu");

	for (u8 c = 1; c < MAX_SECTIONS; c++){
		Section *sect = Menu::getSection(c);

		if (sect){
			oslDrawImageXY(sect->GetSplashIcon(), xPos + 50 + c * 10, yPos + 50);
		}
		else{
			break;
		}
	}
}

OSL_IMAGE* MainSection::GetSplashIcon(){

}

void MainSection::UnloadResources(){

}

void MainSection::LoadResources(){

}