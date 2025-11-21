# # # # # # # # # # # # # # # # # # # # # # # # # #
# Author: GpapPeaky George Papamatthaiakis        
# https://github.com/GpapPeaky				
#
# Kallergis Engine Makefile (Object-Based)
# # # # # # # # # # # # # # # # # # # # # # # # # #

### UNUSED CHECKS
UNUSEDVAR = -Wunused-variable
UNUSEDFUNC = -Wunused-function
UNUSED = $(UNUSEDVAR) $(UNUSEDFUNC)

### COMPILER
CC = g++
CVER = -std=c++23
CFLAGS = -lm -Ofast -lstdc++

### PATHS
SRCPATH = src/
DSTPATH = bin/
OBJECTS = obj/
THIRDPARTYFLG = ThirdParty/
RESOURCES = scripts/resource.rc

### SDL / Third-Party
SDLFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
SDL2LIB = -L$(THIRDPARTYFLG)SDL2/lib
SDL2INC = -I$(THIRDPARTYFLG)SDL2/include

### PeakyGUI
PGUIPATH = $(THIRDPARTYFLG)PeakyGUI/src/
PGUISRC = \
$(PGUIPATH)pgui_action.cpp $(PGUIPATH)pgui_button.cpp $(PGUIPATH)pgui_call.cpp $(PGUIPATH)pgui_cleanup.cpp \
$(PGUIPATH)pgui_component.cpp $(PGUIPATH)pgui_debug.cpp $(PGUIPATH)pgui_draw.cpp $(PGUIPATH)pgui_event.cpp \
$(PGUIPATH)pgui_item.cpp $(PGUIPATH)pgui_load.cpp $(PGUIPATH)pgui_primitives.cpp

### ENGINE SOURCE
DEFSRC = \
$(PGUISRC) \
$(SRCPATH)KallergisEngine.cpp \
$(SRCPATH)SDL2_Camera.cpp \
$(SRCPATH)SDL2_Window.cpp \
$(SRCPATH)SDL2_Pixel.cpp \
$(SRCPATH)SDL2_CleanUp.cpp \
$(SRCPATH)SDL2_Events.cpp \
$(SRCPATH)SDL2_Images.cpp \
$(SRCPATH)SDL2_TextureFonts.cpp \
$(SRCPATH)KENG_Parser.cpp \
$(SRCPATH)KENG_Map.cpp \
$(SRCPATH)KENG_Province.cpp \
$(SRCPATH)KENG_Region.cpp \
$(SRCPATH)KENG_Country.cpp \
$(SRCPATH)KENG_TimeClock.cpp \
$(SRCPATH)KENG_Unit.cpp \
$(SRCPATH)KENG_Economy.cpp \
$(SRCPATH)KENG_Goods.cpp \
$(SRCPATH)KENG_Player.cpp \
$(SRCPATH)KENG_Leader.cpp \
$(SRCPATH)KENG_Debug.cpp \
$(SRCPATH)KENG_City.cpp \
$(SRCPATH)KENG_Terrain.cpp \
$(SRCPATH)PGUI_GUI.cpp \
$(SRCPATH)PGUI_Overloads.cpp

### Convert all sources to objects in obj/
OBJ = $(DEFSRC:%=$(OBJECTS)%.o)

### Executable name
EXEC_NAME = keng.exe

# -----------------------------------------
# Rules
# -----------------------------------------

# Main build
def: $(DSTPATH)$(EXEC_NAME)
	@echo Running $(EXEC_NAME)
	$(DSTPATH)$(EXEC_NAME)

# Link final executable
$(DSTPATH)$(EXEC_NAME): $(OBJ) $(OBJECTS)resources.o
	@mkdir -p $(DSTPATH)
	$(CC) $(CVER) $(SDL2LIB) $(SDL2INC) $^ -o $@ $(SDLFLAGS) $(CFLAGS)

# Compile each .cpp → obj/.o
$(OBJECTS)%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CVER) $(SDL2INC) -c $< -o $@

# Resource compilation
$(OBJECTS)resources.o:
	@mkdir -p $(OBJECTS)
	windres $(RESOURCES) -O coff -o $(OBJECTS)resources.o

### Debug build with unused warnings
def-unsd: CFLAGS += $(UNUSED)
def-unsd: def

### Tools
vxx:
	g++ $(CVER) scripts/cxxver.cpp -o bin/cxxver

vxxDebug:
	@echo Using CC: $(CC)
	@which $(CC)
	@$(CC) --version

paths:
	@echo CURRENT DIRECTORY: "$(CURDIR)"
	@echo DSTPATH: "$(DSTPATH)"
	@echo SRCPATH: "$(SRCPATH)"
	@echo Executable: "$(DSTPATH)$(EXEC_NAME)"

clean:
	@echo Cleaning executables and obj files...
	@if exist "$(DSTPATH)" (rmdir /S /Q "$(DSTPATH)")
	@if exist "$(OBJECTS)" (rmdir /S /Q "$(OBJECTS)")
	@mkdir "$(DSTPATH)"
	@mkdir "$(OBJECTS)"
	@echo Clean complete.

test:
	@echo Makefile test OK.
