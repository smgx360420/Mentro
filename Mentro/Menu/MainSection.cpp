#include "MainSection.h"

//All updates must be relative to the 'world' coordinates supplied
void MainSection::Update(u32 xPos, u32 yPos){

}

//All renders must be relative to the 'world' coordinates supplied
void MainSection::Render(u32 xPos, u32 yPos){
	oslDrawRect(xPos, yPos, xPos + 240, yPos + 272, RGBA(0, 255, 0, 255));
}

OSL_IMAGE* MainSection::GetSplashIcon(){

}

void MainSection::UnloadResources(){

}

void MainSection::LoadResources(){

}