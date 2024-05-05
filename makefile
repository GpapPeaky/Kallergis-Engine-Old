CC = g++
CFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
LIBFLAG = -Lsrc/lib
INCLUDEFLAG = -Isrc/include
SRCPATH = src/

main.exe: $(SRCPATH)init_win.cpp $(SRCPATH)_main.cpp $(SRCPATH)province.cpp $(SRCPATH)regions.cpp $(SRCPATH)init_map.cpp $(SRCPATH)country.cpp $(SRCPATH)map.cpp $(SRCPATH)pixels.cpp $(SRCPATH)events.cpp
	$(CC) $(LIBFLAG) $(INCLUDEFLAG) $^ -o  main $(CFLAGS)

clean:
	rm -f main.exe
