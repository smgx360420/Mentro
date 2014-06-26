#include "PBPParse.h"

u32 count = 0;

void PBPParse::Parse(const char *file){
	fid = sceIoOpen(file, PSP_O_RDONLY, 0777);

	if (fid >= 0)
	{
		if (sceIoRead(fid, &header, sizeof(PBPHeader)) == sizeof(PBPHeader)){

			char *temp = (char*)malloc(header.icon0 - header.sfo);
			sceIoLseek(fid, header.icon0, SEEK_SET);
			sceIoRead(fid, temp, header.icon0 - header.sfo);
			SceUID sfoFile = sceIoOpen("ms0:/TMP/PARAM.SFO", PSP_O_CREAT | PSP_O_WRONLY, 0777);
			sceIoWrite(sfoFile, temp, header.icon0 - header.sfo);
			sceIoClose(sfoFile);
			free(temp);

			temp = (char*)malloc(header.icon1 - header.icon0);
			sceIoLseek(fid, header.icon0, SEEK_SET);
			sceIoRead(fid, temp, header.icon1 - header.icon0);
			SceUID icoFile = sceIoOpen("ms0:/TMP/ICON0.PNG", PSP_O_CREAT | PSP_O_WRONLY, 0777);
			sceIoWrite(icoFile, temp, header.icon1 - header.icon0);
			sceIoClose(icoFile);
			if (header.icon1 - header.icon0 > 0){
				icon = oslLoadImageFilePNG("ms0:/TMP/ICON0.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
			}
			free(temp);

			temp = (char*)malloc(header.snd - header.pic1);
			sceIoLseek(fid, header.pic1, SEEK_SET);
			sceIoRead(fid, temp, header.snd - header.pic1);
			SceUID picFile = sceIoOpen("ms0:/TMP/PIC1.PNG", PSP_O_CREAT | PSP_O_WRONLY, 0777);
			sceIoWrite(picFile, temp, header.snd - header.pic1);
			sceIoClose(picFile);
			if (header.snd - header.pic1 > 0){
				pic = oslLoadImageFilePNG("ms0:/TMP/PIC1.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
			}
			free(temp);

			sceIoClose(fid);
		}
	}
}