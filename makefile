# Globals

CC = g++
CVER = -std=c++17 # C/C++23
SDLFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
CFLAGS = -lm -Ofast
LIBFLAG = -Lsrc/lib
INCLUDEFLAG = -Isrc/include
SRCPATH = src/
DSTPATH = bin/
NONCONSOLEWIN = -Wl,--subsystem,windows # Hides the console and all prints
MWINDOWS = -mwindows # Same as the above
# $(CURDIR) is built-in for make to find the absolute path of the user dir

# Main

EXEC_NAME = keng
DEFSRC =  $(SRCPATH)init_win.cpp $(SRCPATH)_main.cpp $(SRCPATH)province.cpp $(SRCPATH)regions.cpp $(SRCPATH)init_map.cpp $(SRCPATH)country.cpp $(SRCPATH)map.cpp $(SRCPATH)pixels.cpp $(SRCPATH)events.cpp $(SRCPATH)font.cpp $(SRCPATH)primes.cpp $(SRCPATH)hashtable.cpp 

# Hashtable

HASH_EXEC_NAME = hash
HSRC = $(SRCPATH)hashmain.cpp $(SRCPATH)primes.cpp $(SRCPATH)hashtable.cpp

# Pixels

PIXELS_EXEC_NAME = pixels
PSRC = $(SRCPATH)pixels.cpp $(SRCPATH)pixelsmain.cpp $(SRCPATH)country.cpp $(SRCPATH)map.cpp $(SRCPATH)init_win.cpp $(SRCPATH)init_map.cpp $(SRCPATH)province.cpp $(SRCPATH)primes.cpp $(SRCPATH)hashtable.cpp

def: $(DEFSRC)
	@echo Compiling Main (Default), and running 
	$(CC) $(CVER) $(LIBFLAG) $(INCLUDEFLAG) $^ -o $(DSTPATH)$(EXEC_NAME) $(SDLFLAGS) $(CFLAGS)
	$(DSTPATH)$(EXEC_NAME).exe
	
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
	
hash: $(HSRC)
	@echo Hashtable test.
	$(CC) $(CVER) $(LIBFLAG) $(INCLUDEFLAG) $^ -o $(DSTPATH)$(HASH_EXEC_NAME) $(SDLFLAGS) $(CFLAGS)
	$(DSTPATH)$(HASH_EXEC_NAME).exe

# The country source is included to remove some errors of undefined references... pretty bad code but it is for testing anyway...
pixels: $(PSRC)
	@echo Pixel test.
	$(CC) $(CVER) $(LIBFLAG) $(INCLUDEFLAG) $^ -o$(DSTPATH)$(PIXELS_EXEC_NAME) $(SDLFLAGS) $(CFLAGS)
	$(DSTPATH)$(PIXELS_EXEC_NAME).exe

# WARNING: THE FLAGS HAVE TO BE AT THE END OF OF THE MAKE COMMAND, OR ELSE IT WILL NOT WORK

# Compiles all executables
all:
	@echo Compiling all executables...
	$(CC) $(CVER) $(LIBFLAG) $(INCLUDEFLAG) $(DEFSRC) -o $(DSTPATH)$(EXEC_NAME) $(SDLFLAGS) $(CFLAGS)
	@echo -DEF COMPLETED
	$(CC) $(CVER) $(LIBFLAG) $(INCLUDEFLAG) $(PSRC) -o $(DSTPATH)$(PIXELS_EXEC_NAME) $(SDLFLAGS) $(CFLAGS)
	@echo -PIXELS COMPLETED
	$(CC) $(CVER) $(LIBFLAG) $(INCLUDEFLAG) $(HSRC) -o $(DSTPATH)$(HASH_EXEC_NAME) $(SDLFLAGS) $(CFLAGS)
	@echo -HASH COMPLETED
	@echo Compilation completed.
