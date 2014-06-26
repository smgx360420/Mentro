#pragma once
#include <oslib\oslib.h>
#include "SFOParse.h"
#include <pspiofilemgr.h>

class PBPParse
{
private:
	SceUID fid;
public:
	void Parse(const char *file);
	OSL_IMAGE* icon;
	OSL_IMAGE* pic;
	SFOParse sfo;
	typedef struct{
		u8 Magic[4];
		u32 ver;
		u32 sfo;
		u32 icon0;
		u32 icon1;
		u32 pic0;
		u32 pic1;
		u32 snd;
	}PBPHeader;
	PBPHeader header;
};

