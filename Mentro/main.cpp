#include <pspsdk.h>
#include "Callbacks.h"
#include "Menu\Menu.h"

//TODO Change the Name of the homebrew
PSP_MODULE_INFO("Mentro", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);


char app_start_path[256];
int app_start_type;
int app_start_extra;

#ifdef VHBL
//vhbl related
typedef struct
{
	unsigned long APIVersion;
	char Credits[32];
	char VersionName[32];
	char *BackgroundFilename;
	char *filename;
} tMenuApi;

int xstrtoi(char * str, int len)
{
	int val;
	int c;
	int i;
	val = 0;
	for (i = 0; i < len; i++){
		c = *(str + i);
		if (c >= '0' && c <= '9') {
			c -= '0';
		}
		else if (c >= 'A' && c <= 'F') {
			c = (c - 'A') + 10;
		}
		else if (c >= 'a' && c <= 'f') {
			c = (c - 'a') + 10;
		}
		else {
			return 0;
		}
		val *= 16;
		val += c;
	}
	return val;
};
#endif

int main(int argc, char *argv[])
{

#ifdef VHBL
	char * ebootPath = NULL;

	if (argc > 1) //parse second argument to get the vhbl eboot load path (hbl)
	{
		int apiAddr = 0;
		char * hex = argv[1];

		*(hex + 8) = 0;
		apiAddr = xstrtoi(hex, 8);

		if (apiAddr)
		{
			tMenuApi * settings;
			settings = (tMenuApi *)apiAddr;
			ebootPath = settings->filename;
		};
	};
#endif

	SetupCallbacks();

	pspDebugScreenInit();
	pspDebugScreenClear();

	pspDebugScreenPrintf("Starting Menu...");

	Menu::setAppPath(argv[0]);
	char* appToLaunchPath = Menu::Start();


#ifdef VHBL
	strcpy(ebootPath,appToLaunchPath);
#endif

	//Exit the menu
	sceKernelExitGame();
	return 0;
}