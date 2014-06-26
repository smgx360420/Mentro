#pragma once
#include "Section.h"
#include "../Common.h"
#include "Menu.h"
#include "../File/SFOParse.h"
#include "../File/FileManager.h"
#include <psprtc.h>

class MainSection : public Section
{
public:
	//All updates must be relative to the 'world' coordinates supplied
	virtual void Update(u32 xPos, u32 yPos);

	//All renders must be relative to the 'world' coordinates supplied
	virtual void Render(u32 xPos, u32 yPos);

	virtual OSL_IMAGE* GetSplashIcon();

	virtual void UnloadResources();
	virtual void LoadResources();
};

