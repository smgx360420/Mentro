TARGET = MENTRO
OBJS   = main.o Callbacks.o Menu/Menu.o Menu/Wave.o
 
INCDIR   =
CFLAGS   = -G0 -Wall -O2 -D VHBL
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS  = $(CFLAGS)
 
LIBDIR  = libs
LDFLAGS =
LIBS    = -lstdc++ -lpng -lz -lm -losl -lpspsdk -ljpeg
 
BUILD_PRX = 1 
 
EXTRA_TARGETS   = EBOOT.PBP
PSP_EBOOT_TITLE = Mentro

#PSP_EBOOT_ICON= ICON0.png
#PSP_EBOOT_PIC1= PIC1.png
#PSP_EBOOT_SND0= SND0.at3
 
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak