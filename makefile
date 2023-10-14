PROJECTNAME := 3DOBJ

FILENAME = 3dobj
DATE = $(shell date +%Y%m%d)
ARCHIVEFILENAME = $(PROJECTNAME)_$(DATE)

DEPPATH = dep
BINPATH = bin
DEBUGPATH = .
OBJPATH = obj
SRCPATH = .
LIBPATH = lib
ARCHIVEPATH = .

vpath %.cpp $(SRCPATH)
vpath %.h $(SRCPATH)
vpath %.o $(OBJPATH)
vpath %.d $(DEPPATH)

CPP = g++

SOURCES = \
	main.cpp \
	amigafile.cpp \
	cube.cpp \
	face.cpp \
	object3d.cpp \
	rotation.cpp \
	thorus.cpp \
	vector3d.cpp

CPPFLAGS = -g3 -Wall -std=c++1z -I $(SRCPATH)

# ---

$(OBJPATH)/%.o : %.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(DEPPATH)/%.d : %.cpp
	@set -e; rm -f $@; \
	$(CPP) -MM $(CPPFLAGS) $< > $(basename $@).$$$$; \
	sed 's,\($*\)\.o[ :]*,$(OBJPATH)/\1.o $@ : ,g' < $(basename $@).$$$$ > $@; \
	rm -f $(basename $@).$$$$

$(FILENAME) : $(SOURCES:.cpp=.o)
	$(CPP)  \
	$^  \
	`sdl2-config --libs --cflags` -lSDL2_image \
	-o $@

include $(addprefix $(DEPPATH)/, $(SOURCES:.cpp=.d))

# ---

.PHONY: tabify
tabify : srcfiles 
	cat $< | xargs -i emacs --batch --file {} -f mark-whole-buffer -f tabify -f save-buffer

.PHONY: untabify
untabify : srcfiles 
	cat $< | xargs -i emacs --batch --file {} -f mark-whole-buffer -f untabify -f save-buffer

# --- 
.PHONY : clean
clean :
	-rm -f $(DEPPATH)/*
	-rm -f $(OBJPATH)/*

.PHONY : realclean
realclean : clean

	find . -type f \( -name '#*#' -or -name '*~' -or -name '*.cache' \) -print0 | xargs -0r rm -f 


