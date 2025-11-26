#
# Simple Makefile that compiles all .c and .s files in the same folder
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
ifndef GBDK_HOME
	GBDK_HOME = ../
endif

LCC = $(GBDK_HOME)bin/lcc

GBDK_ROM_BANKING = ON
ifdef GBDK_DEBUG
	LCCFLAGS += -debug -v
endif
ifdef GBDK_ROM_BANKING
	LCCFLAGS += -Wl-yt0x1B
	LCCFLAGS += -Wm-ya4
	LCCFLAGS += -autobank
endif


# You can set the name of the .gb ROM file here
PROJECTNAME    = proofOfConcept

BINS	    = $(PROJECTNAME).gb
CSOURCES   := $(wildcard *.c)
ASMSOURCES := $(wildcard *.s)
OBJECTS    := $(CSOURCES:.c=.o) $(ASMSOURCES:.s=.o)
all:	$(BINS)

debug:
	@$(MAKE) GBDK_DEBUG=1

RM = rm -f
ifeq ($(OS),Windows_NT)
	# Use Windows-style 'del' command
	# /F = Force, /Q = Quiet (no prompting)
	RM = del /F /Q
endif

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | sed s/mkdir\ \-p/mkdir/ | grep -v make >> compile.bat

# Compile and link all source files in a single call to LCC
$(BINS):	$(OBJECTS)
	$(LCC) $(LCCFLAGS) -o $@ $(OBJECTS)
	$(RM) $(OBJECTS) *.asm *.lst *.sym *.ihx

%.o: %.c
	$(LCC) $(LCCFLAGS) -DFILE_NAME=$(basename $(<F)) -c -o $@ $<

%.o: %.s
	$(LCC) $(LCCFLAGS) -c -o $@ $<

clean:
	$(RM) *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm *.noi *.rst

