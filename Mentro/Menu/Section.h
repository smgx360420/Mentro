#pragma once

#include <oslib\oslib.h>

//Section allows for each bit of the menu to be separated from the rest of the code
class Section
{
public:
	Section();

	//All updates must be relative to the 'world' coordinates supplied
	virtual void Update(u32 xPos, u32 yPos) = 0;

	//All renders must be relative to the 'world' coordinates supplied
	virtual void Render(u32 xPos, u32 yPos) = 0;

	virtual OSL_IMAGE* GetSplashIcon() = 0;

	virtual void UnloadResources() = 0;
	virtual void LoadResources() = 0;
	~Section();
};

