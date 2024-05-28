CC = g++
CFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
LIBFLAG = -Lsrc/lib
INCLUDEFLAG = -Isrc/include
SRCPATH = src/
EXEC_NAME = projectcandia

projectcandia.exe: $(SRCPATH)init_win.cpp $(SRCPATH)_main.cpp $(SRCPATH)province.cpp $(SRCPATH)regions.cpp $(SRCPATH)init_map.cpp $(SRCPATH)country.cpp $(SRCPATH)map.cpp $(SRCPATH)pixels.cpp $(SRCPATH)events.cpp $(SRCPATH)font.cpp
	@echo Compiling executable...
	$(CC) $(LIBFLAG) $(INCLUDEFLAG) $^ -o  $(EXEC_NAME) $(CFLAGS)

clean:
	@echo Cleaning executable...
	del /F /Q $(EXEC_NAME).exe

test:
	@echo Makefile test.
	