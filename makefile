# Main

CC = g++
CFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Ofast -Wunused-variable -lm
LIBFLAG = -Lsrc/lib
INCLUDEFLAG = -Isrc/include
SRCPATH = src/
EXEC_NAME = projectcandia

# Hashtable

HFLAGS = -Wunused-variable
HASH_EXEC_NAME = hash

def: $(SRCPATH)init_win.cpp $(SRCPATH)_main.cpp $(SRCPATH)province.cpp $(SRCPATH)regions.cpp $(SRCPATH)init_map.cpp $(SRCPATH)country.cpp $(SRCPATH)map.cpp $(SRCPATH)pixels.cpp $(SRCPATH)events.cpp $(SRCPATH)font.cpp
	@echo Compiling and running executable...
	$(CC) $(LIBFLAG) $(INCLUDEFLAG) $^ -o  $(EXEC_NAME) $(CFLAGS)
	$(EXEC_NAME).exe
	
clean:
	@echo Cleaning executable...
	del /F /Q $(EXEC_NAME).exe
	del /F /Q $(HASH_EXEC_NAME).exe

test:
	@echo Makefile test.
	
hash:
	@echo Hashtable test.
	$(CC) $(LIBFLAG) $(INCLUDEFLAG) $(SRCPATH)hashmain.cpp $(SRCPATH)primes.cpp $(SRCPATH)hashtable.cpp -o $(HASH_EXEC_NAME) $(CFLAGS) $(HFLAGS)
	$(HASH_EXEC_NAME).exe