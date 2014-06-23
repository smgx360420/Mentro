#include "Section.h"

Section::~Section()
{

}

Section::Section()
{

}

//All updates must be relative to the 'world' coordinates supplied
void Section::Update(u32 xPos, u32 yPos){}

//All renders must be relative to the 'world' coordinates supplied
void Section::Render(u32 xPos, u32 yPos)
{
}

OSL_IMAGE* Section::GetSplashIcon(){}

void Section::UnloadResources(){}
void Section::LoadResources(){}