# Main

CC = g++
CFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wunused-variable -lm -Ofast
LIBFLAG = -Lsrc/lib
INCLUDEFLAG = -Isrc/include
SRCPATH = src/
EXEC_NAME = projectcandia

# Hashtable

HFLAGS = -Wunused-variable
HASH_EXEC_NAME = hash

# Pixels

PFLAGS = -Wunused-variable
PIXELS_EXEC_NAME = pixels
MWINDOWS = -mwindows
NONCONSOLEWIN = -Wl,--subsystem,windows # Hides the console and all prints

def: $(SRCPATH)init_win.cpp $(SRCPATH)_main.cpp $(SRCPATH)province.cpp $(SRCPATH)regions.cpp $(SRCPATH)init_map.cpp $(SRCPATH)country.cpp $(SRCPATH)map.cpp $(SRCPATH)pixels.cpp $(SRCPATH)events.cpp $(SRCPATH)font.cpp $(SRCPATH)primes.cpp $(SRCPATH)hashtable.cpp 
	$(CC) $(LIBFLAG) $(INCLUDEFLAG) $^ -o  $(EXEC_NAME) $(MWINDOWS) $(CFLAGS)
	$(EXEC_NAME).exe
	
clean:
	@echo Cleaning executable...
	del /F /Q $(EXEC_NAME).exe
	del /F /Q $(HASH_EXEC_NAME).exe
	del /F /Q $(PIXELS_EXEC_NAME).exe

test:
	@echo Makefile test.
	
hash: $(SRCPATH)hashmain.cpp $(SRCPATH)primes.cpp $(SRCPATH)hashtable.cpp
	@echo Hashtable test.
	$(CC) $(LIBFLAG) $(INCLUDEFLAG) $^ -o $(HASH_EXEC_NAME) $(CFLAGS) $(HFLAGS)
	$(HASH_EXEC_NAME).exe

# The country source is included to remove some errors of undefined references... pretty bad code but it is for testing anyway...
pixels: $(SRCPATH)pixels.cpp $(SRCPATH)pixelsmain.cpp $(SRCPATH)country.cpp
	@echo Pixel test.
	$(CC) $(LIBFLAG) $(INCLUDEFLAG) $^ -o $(PIXELS_EXEC_NAME) $(CFLAGS)
	$(PIXELS_EXEC_NAME).exe

# WARNING: THE FLAGS HAVE TO BE AT THE END OF OF THE MAKE COMMAND, OR ELSE IT WILL NOT WORK
