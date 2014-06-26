#pragma once
#include "Section.h"
class GameSelector :
	public Section
{
public:
	//All updates must be relative to the 'world' coordinates supplied
	virtual void Update(u32 xPos, u32 yPos);

	//All renders must be relative to the 'world' coordinates supplied
	virtual void Render(u32 xPos, u32 yPos);

	virtual OSL_IMAGE* GetSplashIcon();

	virtual int GetSplashX();
	virtual int GetSplashY();

	virtual void UnloadResources();
	virtual void LoadResources();
};
