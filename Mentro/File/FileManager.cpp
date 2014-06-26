#include "FileManager.h"

SceUID dirId = NULL;
SceIoDirent dirent;
int dirStatus = 1;
char filename[256];

int FileManager::ChangeDir(const char* path)
{
	return sceIoChdir(path);
}

int FileManager::DirExists(const char* path)
{
	SceUID dir = sceIoDopen(path);
	if (dir >= 0){
		sceIoDclose(dir);
		return 1;
	}
	else {
		return -1;
	}
}

int FileManager::FileExists(const char* path)
{
	SceUID dir = sceIoOpen(path, PSP_O_RDONLY, 0777);
	if (dir >= 0){
		sceIoClose(dir);
		return 1;
	}
	else {
		return 0;
	}
}

int FileManager::OpenDir(const char* path)
{
	dirStatus = 1;
	dirId = sceIoDopen(path);
	sceIoDread(dirId, &dirent);
	sceIoDread(dirId, &dirent);
	return dirId;
}

int FileManager::CloseDir()
{
	if (dirId != NULL)
	{
		sceIoDclose(dirId);
		dirId = NULL;
		return 1;
	}
	return 0;
}

int FileManager::Next()
{
	if (dirId > NULL && dirStatus > 0)
	{
		dirStatus = sceIoDread(dirId, &dirent);
	}
	return dirStatus;
}

char* FileManager::GetNextFileName()
{
	if (dirId > NULL && dirStatus > 0)
	{
		if(dirStatus >= 0)strcpy(filename, dirent.d_name);
	}
	return filename;
}

int FileManager::IsNextDir()
{
	return FIO_S_ISDIR(dirent.d_stat.st_mode);
}