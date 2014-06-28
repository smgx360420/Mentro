#pragma once
#include "Section.h"
#include "../File/PBPParse.h"
#include "../Config/Config.h"
#include "../Common.h"
#include "../File/FileManager.h"
#include "Menu.h"

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

