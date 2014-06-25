#pragma once
#include <pspiofilemgr.h>
#include <string.h>

class FileManager
{
public:
	static int ChangeDir(const char *path);
	static int DirExists(const char *path);
	static int FileExists(const char *filename);
	static int OpenDir(const char *path);
	static int CloseDir();
	static int NextFileExists();
	static char* GetNextFileName();
};

