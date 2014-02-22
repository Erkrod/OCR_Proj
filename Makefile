#get lib sdl ready to compile
$(shell python pkgconfig_changepath.py)	

CC	:= gcc
CFLAGS	:= -g
LDFLAGS := -lm

MODULES   := Model Control View
SRC_DIR   := $(addprefix src/,$(MODULES))

MODEL_LIB := Model

CONTROL_LIB := Control

VIEW_LIB := View

ifeq ($(SESSION),ubuntu)
	CFLAGS +=-DLINUX_OS
endif

ifeq ($(OSTYPE),linux)
	CFLAGS +=-DLINUX_OS
endif

ifeq ($(QUAN_VERSION), y)
	CFLAGS +=-DQUAN_VERSION
endif

ifeq ($(GUI_ENABLE),y)

	GUI_FLAG=-DGUI_ENABLE $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
	VIEW_LIB+= display ObjectHandleList ObjectHandle render
	LDFLAGS+= $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)
else
        GUI_FLAG=
       # CFLAGS +=-ansi
endif

MODEL_LIB_DEPEND := $(addprefix build/lib,$(MODEL_LIB))
MODEL_LIB_DEPEND := $(addsuffix .a,$(MODEL_LIB_DEPEND))
MODEL_LIB_COMPILE := $(addprefix -l,$(MODEL_LIB))

CONTROL_LIB_DEPEND := $(addprefix build/lib,$(CONTROL_LIB))
CONTROL_LIB_DEPEND := $(addsuffix .a,$(CONTROL_LIB_DEPEND))
CONTROL_LIB_COMPILE := $(addprefix -l,$(CONTROL_LIB))

VIEW_LIB_DEPEND := $(addprefix build/lib,$(VIEW_LIB))
VIEW_LIB_DEPEND := $(addsuffix .a,$(VIEW_LIB_DEPEND))
VIEW_LIB_COMPILE := $(addprefix -l,$(VIEW_LIB))

INCLUDES  := $(addprefix -Iinc/,$(MODULES)) -Iinc/uthash

VPATH = $(SRC_DIR) src



.PHONY: all clean test

all: ChessXIV

test: ModelUnitTest

clean:
	rm build/*
	rm bin/*

build/%.o: %.c
	
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(GUI_FLAG)

build/lib%.a: build/%.o
	ar rc $@ $<
	ranlib $@

TestCharArray: build/ExampleCharArray.o
	$(CC) $(CFLAGS) $< -o bin/$@

TestUTArray: build/utarray_example.o
	$(CC) $(CFLAGS) $< -o bin/$@
	
	
PostProcessing: build/TestPostProcessing.o $(MODEL_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(VIEW_LIB_DEPEND)
		$(CC) build/TestPostProcessing.o -Lbuild $(VIEW_LIB_COMPILE) $(LDFLAGS) -o bin/$@ $(CFLAGS)