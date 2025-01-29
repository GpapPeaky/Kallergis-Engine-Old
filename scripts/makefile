# # # # # # # # # # # # # # # # # # # # # # # # # #
# Author: GpapPeaky George Papamatthaiakis        
# https://github.com/GpapPeaky				
#
# Kallergis Engine Makefile
#
# # # # # # # # # # # # # # # # # # # # # # # # # #

# Unused Checks For Debugging

UNUSEDVAR = -Wunused-variable
UNUSEDFUNC = -Wunused-function
UNUSED = $(UNUSEDVAR) $(UNUSEDFUNC)

# Globals

CC = g++
CVER = -std=c++23 # C/C++23 Maybe..?
SDLFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
CFLAGS = -lm -Ofast -lstdc++ -pthread
RESOURCES = scripts/resource.rc
OBJECTS = obj/
THIRDPARTYFLG = ThirdParty/
SDL2LIB = -L$(THIRDPARTYFLG)SDL2/lib
SDL2INC = -I$(THIRDPARTYFLG)SDL2/include
PGUIPATH = $(THIRDPARTYFLG)PeakyGUI/src/
# PGUISRC = $(PGUIPATH)pgui_button.cpp $(PGUIPATH)pgui_call.cpp $(PGUIPATH)pgui_component.cpp $(PGUIPATH)pgui_draw.cpp $(PGUIPATH)pgui_item.cpp $(PGUIPATH)pgui_event.cpp $(PGUIPATH)pgui_primitives.cpp
SRCPATH = src/
DSTPATH = bin/
NONCONSOLEWIN = -Wl,--subsystem,windows # Hides the console and all prints
MWINDOWS = -mwindows # Same as the above
# $(CURDIR) is built-in for make to find the absolute path of the user dir

# PeakyGUI

PGUISRC = $(PGUIPATH)pgui_action.cpp $(PGUIPATH)pgui_button.cpp $(PGUIPATH)pgui_call.cpp $(PGUIPATH)pgui_cleanup.cpp \
$(PGUIPATH)pgui_component.cpp $(PGUIPATH)pgui_debug.cpp $(PGUIPATH)pgui_draw.cpp $(PGUIPATH)pgui_event.cpp \
$(PGUIPATH)pgui_event.cpp $(PGUIPATH)pgui_item.cpp $(PGUIPATH)pgui_load.cpp $(PGUIPATH)pgui_primitives.cpp

# Main

# WARN: THE FLAGS HAVE TO BE AT THE END OF OF THE MAKE COMMAND, OR ELSE IT WILL NOT WORK

EXEC_NAME = keng
DEFSRC = \
$(PGUISRC)\
$(SRCPATH)KallergisEngine.cpp\
$(SRCPATH)SDL2_Camera.cpp\
$(SRCPATH)SDL2_Window.cpp\
$(SRCPATH)SDL2_Pixel.cpp\
$(SRCPATH)SDL2_CleanUp.cpp\
$(SRCPATH)SDL2_Events.cpp\
$(SRCPATH)SDL2_Images.cpp\
$(SRCPATH)SDL2_TextureFonts.cpp\
$(SRCPATH)KENG_Parser.cpp\
$(SRCPATH)KENG_Map.cpp\
$(SRCPATH)KENG_Province.cpp\
$(SRCPATH)KENG_Region.cpp\
$(SRCPATH)KENG_Country.cpp\
$(SRCPATH)KENG_TimeClock.cpp\
$(SRCPATH)KENG_Unit.cpp\
$(SRCPATH)KENG_Economy.cpp\
$(SRCPATH)KENG_Goods.cpp\
$(SRCPATH)KENG_Player.cpp\
$(SRCPATH)KENG_Leader.cpp\
$(SRCPATH)KENG_Debug.cpp\
$(SRCPATH)KENG_City.cpp\
$(SRCPATH)PGUI_GUI.cpp\
$(SRCPATH)PGUI_Overloads.cpp

# Compiles the default engine

def: $(DEFSRC)
	@echo Compiling Main (Default), and running
	windres $(RESOURCES) -O coff -o $(OBJECTS)resources.o
	$(CC) $(CVER) $(SDL2LIB) $(SDL2INC) $^ $(OBJECTS)resources.o -o $(DSTPATH)$(EXEC_NAME) $(SDLFLAGS) $(CFLAGS)
	$(DSTPATH)$(EXEC_NAME).exe

# Unused Variable And Functions Compiling For Debugging

def-unsd: $(DEFSRC)
	@echo Compiling Main (Default), and running 
	windres $(RESOURCES) -O coff -o $(OBJECTS)resources.o
	$(CC) $(CVER) $(SDL2LIB) $(SDL2INC) $(UNUSED) $^ -o $(DSTPATH)$(EXEC_NAME) $(SDLFLAGS) $(CFLAGS)
	$(DSTPATH)$(EXEC_NAME).exe

obj:
	@echo Compiling resources
	windres $(RESOURCES) -O coff -o $(OBJECTS)resources.o

# CXX Version Control, Required Compiler For <thread> <mutex> 

vxx:
	 g++ $(CVER) scripts/cxxver.cpp -o bin/cxxver

vxxDebug:
	@echo Using CC: $(CC)
	@which $(CC)
	@$(CC) --version

# Print the local paths
	
paths:
	@echo CURRENT DIRECTORY: "$(CURDIR)"
	@echo DSTPATH: "$(DSTPATH)"
	@echo SRCPATH: "$(SRCPATH)"
	@echo EXECUTABLES:
	@echo "$(DSTPATH)$(EXEC_NAME).exe"
	@echo "$(DSTPATH)$(HASH_EXEC_NAME).exe"
	@echo "$(DSTPATH)$(PIXELS_EXEC_NAME).exe"

clean:
	@echo Cleaning executables...
	@if exist "$(DSTPATH)" (rmdir /S /Q "$(DSTPATH)" && mkdir "$(DSTPATH)" && echo All files in $(DSTPATH) cleaned.) else (echo Directory "$(DSTPATH)" not found)

test:
	@echo Makefile test.
