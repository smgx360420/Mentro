#include "PBPParse.h"

u32 count = 0;
OSL_IMAGE *defaultUNKN;

void PBPParse::setDefaultUNKN()
{
	defaultUNKN = oslLoadImageFilePNG("UNKN.PNG", OSL_IN_RAM, OSL_PF_5650);
}

void PBPParse::Parse(const char *file){
	fid = sceIoOpen(file, PSP_O_RDONLY, 0777);

	sceIoMkdir("ms0:/TMP", 0777);
	if (fid >= 0)
	{
		if (sceIoRead(fid, &header, sizeof(PBPHeader)) == sizeof(PBPHeader)){

			char *temp = (char*)malloc(header.icon0 - header.sfo);
			sceIoLseek(fid, header.sfo, PSP_SEEK_SET);
			sceIoRead(fid, temp, header.icon0 - header.sfo);
			SceUID sfoFile = sceIoOpen("ms0:/TMP/PARAM.SFO", PSP_O_CREAT | PSP_O_WRONLY, 0777);
			sceIoWrite(sfoFile, temp, header.icon0 - header.sfo);
			sceIoClose(sfoFile);
			free(temp);
			sfo.Parse("ms0:/TMP/PARAM.SFO");

			temp = (char*)malloc(header.icon1 - header.icon0);
			sceIoLseek(fid, header.icon0, PSP_SEEK_SET);
			sceIoRead(fid, temp, header.icon1 - header.icon0);
			SceUID icoFile = sceIoOpen("ms0:/TMP/ICON0.PNG", PSP_O_CREAT | PSP_O_WRONLY, 0777);
			sceIoWrite(icoFile, temp, header.icon1 - header.icon0);
			sceIoClose(icoFile);
			if (header.icon1 - header.icon0 > 0){
				OSL_IMAGE *ico = oslLoadImageFilePNG("ms0:/TMP/ICON0.PNG", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_5650);
				icon = oslScaleImageCreate(ico, OSL_IN_RAM, 64, 64, OSL_PF_5650);
				oslDeleteImage(ico);
				oslWriteImageFilePNG(icon, "ms0:/TMP/ICON0.PNG", 0);
			}
			else{
				icon = oslCreateImageCopy(defaultUNKN, OSL_IN_RAM);
			}
			free(temp);

			temp = (char*)malloc(header.snd - header.pic1);
			sceIoLseek(fid, header.pic1, PSP_SEEK_SET);
			sceIoRead(fid, temp, header.snd - header.pic1);
			SceUID picFile = sceIoOpen("ms0:/TMP/PIC1.PNG", PSP_O_CREAT | PSP_O_WRONLY, 0777);
			sceIoWrite(picFile, temp, header.snd - header.pic1);
			sceIoClose(picFile);
			if (header.snd - header.pic1 > 0){
				pic = oslLoadImageFilePNG("ms0:/TMP/PIC1.PNG", OSL_IN_RAM, OSL_PF_8888);

				OSL_IMAGE *tmpPic = oslScaleImageCreate(pic, OSL_IN_RAM, 128, 128, OSL_PF_8888);
				oslUnswizzleImage(tmpPic);
				oslWriteImageFilePNG(tmpPic, "ms0:/TMP/PIC1SC.PNG", 0);
				oslDeleteImage(tmpPic);
				oslDeleteImage(pic);	//Get rid of the pic file for now, we don't need it
			}
			free(temp);

			sceIoClose(fid);
		}
	}
}