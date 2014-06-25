#include "GameSelector.h"

OSL_IMAGE *splash = NULL;

void GameSelector::LoadResources()
{
}

OSL_IMAGE* GameSelector::GetSplashIcon(){
	if (splash == NULL)splash = oslLoadImageFilePNG("GAME.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_5650);
	return splash;
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
