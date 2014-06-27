#include "SFOParse.h"


void SFOParse::Parse(const char *path)
{
	SceUID sfoFile = sceIoOpen(path, PSP_O_RDONLY, 0777);

	if (sfoFile >= 0)
	{
		if(sceIoRead(sfoFile, &header, sizeof(Header)) != sizeof(Header))return;
		u32 curOff = 0;
		char tmp[64];
		for (int c = 0; c < header.entryNum; c++)
		{
			sceIoRead(sfoFile, &entry, sizeof(IndexTable));
			curOff = sceIoLseek(sfoFile, 0, PSP_SEEK_CUR);	//Get the current offset
			sceIoLseek(sfoFile, header.keyTableOff + entry.KeyOff, PSP_SEEK_SET);	//Seek to the key
			sceIoRead(sfoFile, tmp, 64);

			if (strcmp(tmp, "TITLE_ID") == 0)
			{
				sceIoLseek(sfoFile, header.dataTableOff + entry.DataOff, PSP_SEEK_SET);
				sceIoRead(sfoFile, ID, entry.maxLength);
			}
			else if (strcmp(tmp, "TITLE") == 0)
			{
				sceIoLseek(sfoFile, header.dataTableOff + entry.DataOff, PSP_SEEK_SET);
				sceIoRead(sfoFile, Name, entry.maxLength);
			}
			else if (strcmp(tmp, "REGION") == 0)
			{
				sceIoLseek(sfoFile, header.dataTableOff + entry.DataOff, PSP_SEEK_SET);
				sceIoRead(sfoFile, &region, entry.maxLength);
			}

			sceIoLseek(sfoFile, curOff, PSP_SEEK_SET);	//Return to the index table entry offset
		}

		sceIoClose(sfoFile);
	}
}

char *SFOParse::GetID(){ return ID; }
char *SFOParse::GetName(){ return Name; }
int SFOParse::GetEncoding()
{
	return region;
}