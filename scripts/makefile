# Compiler
CXX = g++

# Paths
SRCP = src/
OBJDIR = obj/
BINDIR = bin/

# SDL2 includes and libs
SDL2I = -IThirdParty/SDL2/include/SDL2
SDL2L = -LThirdParty/SDL2/lib
SDL2F = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Default target
all: $(BINDIR)win.exe

# Link step
$(BINDIR)win.exe:  $(OBJDIR)main.o \
				   $(OBJDIR)SDL2_Event.o \
				   $(OBJDIR)SDL2_InitWin.o \
                   $(OBJDIR)SDL2_Bitmap.o \
				   $(OBJDIR)SDL2_Quad.o \
				   $(OBJDIR)SDL2_Camera.o

	@mkdir -p $(BINDIR)
	$(CXX) $^ $(SDL2L) $(SDL2F) -o $@

# Explicit compile rules for each source file
$(OBJDIR)main.o: $(SRCP)main.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ $(SDL2I)

$(OBJDIR)SDL2_Event.o: $(SRCP)SDL2_Event.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ $(SDL2I)

$(OBJDIR)SDL2_InitWin.o: $(SRCP)SDL2_InitWin.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ $(SDL2I)

$(OBJDIR)SDL2_Bitmap.o: $(SRCP)SDL2_Bitmap.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ $(SDL2I)

$(OBJDIR)SDL2_Quad.o: $(SRCP)SDL2_Quad.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ $(SDL2I)

$(OBJDIR)SDL2_Camera.o: $(SRCP)SDL2_Camera.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ $(SDL2I)

# Utility targets
clean:
	-rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all clean
