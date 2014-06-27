#pragma once
#include <pspsdk.h>
#include <pspiofilemgr.h>
#include <string.h>

class SFOParse
{
public:
	void Parse(const char *path);
	typedef struct{
		u32 magic;
		u32 version;
		u32 keyTableOff;
		u32 dataTableOff;
		u32 entryNum;
	}Header;
	typedef struct{
		u16 KeyOff;
		u16 region;
		u32 length;
		u32 maxLength;
		u32 DataOff;
	}IndexTable;
	char *GetName();
	char *GetID();
	int GetEncoding();
private:
	Header header;
	IndexTable entry;
	char Name[256];
	char ID[16];
	int region;
};

