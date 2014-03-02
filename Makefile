#get lib sdl ready to compile

CC	:= gcc
CFLAGS	:= -g -Wall
LDFLAGS := -lm

#take care of test flags
ifeq ($(TEST_VIEW),y)
	CFLAGS += -DTEST_VIEW -DDEBUG
endif

ifeq ($(DEBUG),y)
	CFLAGS += -DDEBUG
endif

MODULES   := Model Control View
SRC_DIR   := $(addprefix src/,$(MODULES))

MODEL_LIB := Model IsolateCharacter FileIO DIPs Image ImageList

CONTROL_LIB := Control

VIEW_LIB := View DrawFunctions 

GUI_CFLAGS := $(shell pkg-config --cflags gtk+-2.0)
GUI_LFLAGS := $(shell pkg-config --libs gtk+-2.0)


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
	$(CC) $(CFLAGS) $(INCLUDES) $(GUI_CFLAGS) -c $< -o $@

build/lib%.a: build/%.o
	ar rc $@ $<
	ranlib $@

TestCharArray: build/ExampleCharArray.o
	$(CC) $(CFLAGS) $< -o bin/$@

TestUTArray: build/utarray_example.o
	$(CC) $(CFLAGS) $< -o bin/$@

TestPostPo: build/postProcessing.o
	$(CC) $(CFLAGS) $< -o bin/$@

TestView: build/GFXMain.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND)
	$(CC) build/GFXMain.o -Lbuild $(VIEW_LIB_COMPILE) $(CONTROL_LIB_COMPILE) $(GUI_LFLAGS) -o bin/$@ 
	
TestIsolateCharacter: build/TestIsolateCharacter.o $(MODEL_LIB_DEPEND)
	$(CC) build/TestIsolateCharacter.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
	
OCR: build/OCR.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(CC) build/OCR.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 