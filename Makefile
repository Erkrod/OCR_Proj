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

MODEL_LIB := postProcessing IdentifyCharacter Model IsolateCharacter FileIO ImageProcessing Image ImageList

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

VPATH = $(SRC_DIR) src test



.PHONY: all clean test

all: OCR test

test: TestCharArray TestUTArray TestPostPo TestView TestIsolateCharacter TestIdentifyCharacter

clean:
	rm build/* bin/*

build/%.o: %.c	
	$(info Compiling $@)
	@$(CC) $(CFLAGS) $(INCLUDES) $(GUI_CFLAGS) -c $< -o $@

build/lib%.a: build/%.o
	$(info Archiving $@)
	@ar rc $@ $<
	@ranlib $@

TestCharArray: build/ExampleCharArray.o
	$(info Linking $@)
	@$(CC) $(CFLAGS) $< -o bin/$@

TestUTArray: build/utarray_example.o
	$(info Linking $@)
	@$(CC) $(CFLAGS) $< -o bin/$@

TestPostPo: build/TestPostProcessing.o $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestPostProcessing.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@

TestView: build/GFXMain.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/GFXMain.o -Lbuild $(VIEW_LIB_COMPILE) $(CONTROL_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
	
TestIsolateCharacter: build/TestIsolateCharacter.o $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestIsolateCharacter.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
	
TestIdentifyCharacter: build/TestIdentifyCharacter.o $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestIdentifyCharacter.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
	bin/TestIdentifyCharacter
	
OCR: build/OCR.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/OCR.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
