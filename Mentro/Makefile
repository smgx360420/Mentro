TARGET = MENTRO
OBJS   = main.o Callbacks.o Menu/Menu.o Menu/Wave.o Menu/MainSection.o Menu/Section.o Menu/GameSelector.o Config/Config.o File/FileManager.o File/PBPParse.o File/SFOParse.o
 
INCDIR   =
CFLAGS   = -G0 -Wall -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS  = $(CFLAGS)
 
LIBDIR  = libs
LDFLAGS =
LIBS    = -losl -lpng -lz \
         -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu -lpspgum  -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
         -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -ljpeg
 
BUILD_PRX = 1 
 
EXTRA_TARGETS   = EBOOT.PBP
PSP_EBOOT_TITLE = Mentro

PSP_EBOOT_ICON= LGDEF.PNG
PSP_EBOOT_PIC1= WALL.PNG
#PSP_EBOOT_SND0= SND0.at3
 
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak