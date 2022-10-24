CC		= ccpsx
ASM		= asmpsx
LINK	= slink
LIBLNK	= psylib2

ASM_REL=0
ifeq ($(RELMODE),DEBUG)
	ASM_REL=1
endif

CCOPTIONS  = -Wunused -O$(OPTIMIZE) -G0 -comments-c++ -nostdlib -c -D$(RELMODE) -I.. -I.
CCOOPTIONS = -O$(OPTIMIZE) -G0 -comments-c++ -nostdlib -c -DOVERLAY -D$(RELMODE)
ASMOPTIONS = /l /o c+ /o an+ /zd /x /e RELMODE=${ASM_REL}
LINKOPTS = /psx /c /z /li $(RELMODE)
LINKOOPTS = /psx /p /c /li $(RELMODE)

FONT_SRC = font.cpp
TEXT_SRC = text.cpp
SUBTITLE_SRC = subtitle.cpp generated_movie.cpp loadfile.cpp

## build object names from types ##
#CORE_OBJ	= $(patsubst %.c, $(RELMODE)/%.obj, ${CORE_SRC})
#CORE_ASM	= $(patsubst %.asm, $(RELMODE)/%.obj, ${CORE_S})
#FIELD_OBJ	= $(patsubst %.c, $(RELMODE)/%.obf, ${FIELD_SRC})
#MENU_OBJ	= $(patsubst %.c, $(RELMODE)/%.obm, ${MENU_SRC})
#BATTLE_OBJ	= $(patsubst %.c, $(RELMODE)/%.obb, ${BATTLE_SRC})
FONT_OBJ = $(patsubst %.cpp, $(RELMODE)/%.obj, ${FONT_SRC})
SUB_OBJ = $(patsubst %.cpp, $(RELMODE)/%.obj, ${SUBTITLE_SRC})
TEXT_OBJ = $(patsubst %.cpp, $(RELMODE)/%.obj, ${TEXT_SRC})

## list of objects to use for linking ##
## NOTE: you still need to specify them in the ##
## .lk file or they will not be linked at all! ##
#ALL_SRC = $(CORE_OBJ) $(MENU_OBJ) $(BATTLE_OBJ) $(FIELD_OBJ)
#ALL_ASM = $(CORE_ASM)
ALL_SRC = $(FONT_OBJ) $(SUB_OBJ) $(TEXT_OBJ)


#ALL_OBJ = $(ALL_SRC) $(ALL_ASM)
ALL_OBJ = $(ALL_SRC)
## ------- ##

#====================================#
# kernel objects to build ENGINE.BIN #
#====================================#
#$(RELMODE)/%.obj : core/%.c
#	$(CC) $(CCOPTIONS) $< -o $@
#$(RELMODE)/%.obj : core/%.asm
#	$(ASM) $(ASMOPTIONS) $<,$@
#================================#
# menu objects to build MENU.BIN #
#================================#
#$(RELMODE)/%.obm: menu/%.c
#	$(CC) $(CCOPTIONS) $< -o $@
#================================#
# battle objects				 #
#================================#
#$(RELMODE)/%.obb: battle/%.c
#	$(CC) $(CCOPTIONS) $< -o $@
#================================#
# field objects					 #
#================================#
#$(RELMODE)/%.obf: field/%.c
#	$(CC) $(CCOPTIONS) $< -o $@
#====================================#
# subtitle objects                   #
#====================================#
$(RELMODE)/%.obj: code/%.cpp
	$(CC) $(CCOPTIONS) $< -o $@

all: inform $(RELMODE)/${OUTFILE}.cpe

inform:
ifneq ($(RELMODE),RELEASE)
ifneq ($(RELMODE),DEBUG)
	@echo "Invalid configuration "$(RELMODE)" specified."
	@echo "You must specify a configuration when running make, e.g."
	@echo  "make RELMODE=DEBUG"
	@echo  
	@echo  "Possible choices for configuration are 'RELEASE' and 'DEBUG'"
	@exit 1
endif
endif
	@echo "Configuration "$(RELMODE)
	@echo "------------------------"

$(RELMODE)/${OUTFILE}.cpe: ${ALL_OBJ}
	del /q obj\*
	copy $(RELMODE)\*.o* obj\ /y

clean:
	rmdir /q /s $(RELMODE)

rebuild: clean | all

# DO NOT DELETE
