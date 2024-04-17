CC = g++
CFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
LIBFLAG = -Lsrc/lib
INCLUDEFLAG = -Isrc/include
SRCPATH = src/

main.exe: $(SRCPATH)init_win.cpp $(SRCPATH)_main.cpp
	$(CC) $(LIBFLAG) $(INCLUDEFLAG) $^ -o  main $(CFLAGS)

clean:
	rm -f main.exe
