#get lib sdl ready to compile

CC	:= gcc
CFLAGS	:= -Wall
LDFLAGS := -lm

#take care of test flags
ifeq ($(TEST_VIEW),y)
	CFLAGS += -DTEST_VIEW -DDEBUG
endif

ifeq ($(DEBUG),y)
	CFLAGS += -DDEBUG -g
	LDFLAGS += -pg
endif

MODULES   := Model Control View
SRC_DIR   := $(addprefix src/,$(MODULES))

MODEL_LIB := IdentifyCharacter Model postProcessing IsolateCharacter FileIO ImageProcessing Image ImageList

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

test: TestCharArray TestUTArray TestPostPo TestGUI TestIsolateCharacter TestCompile CFTest CropTest RotTest SRTest 

clean:
	rm build/* bin/*

#************************ COMMON BUILD ************************		
build/%.o: %.c	
	$(info Compiling $@)
	@$(CC) $(CFLAGS) $(INCLUDES) $(GUI_CFLAGS) -c $< -o $@

build/lib%.a: build/%.o
	$(info Archiving $@)
	@ar rc $@ $<
	@ranlib $@

#************************ TEST OF PRE PROCESSING ************************	
CFTest:	build/CFTest.o	$(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/CFTest.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@

CropTest: build/CropTest.o	$(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/CropTest.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@
	
RotTest: build/RotTest.o	$(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/RotTest.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@	
	
SRTest: build/SRTest.o	$(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/SRTest.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@		

#************************ TEST OF DATA STRUCTURE ************************	
TestCharArray: build/ExampleCharArray.o
	$(info Linking $@)
	@$(CC) $(CFLAGS) $< -o bin/$@

TestUTArray: build/utarray_example.o
	$(info Linking $@)
	@$(CC) $(CFLAGS) $< -o bin/$@

#************************ TEST OF BIG MODULES ************************		
	
TestPostPo: build/TestPostProcessing.o $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestPostProcessing.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@

TestView: build/GFXMain.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/GFXMain.o -Lbuild $(VIEW_LIB_COMPILE) $(CONTROL_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
	
TestIsolateCharacter: build/TestIsolateCharacter.o $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestIsolateCharacter.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
#	@time bin/TestIsolateCharacter
#	@eog CheckLazyIsolate.ppm
	
TestIdentifyCharacter: build/TestIdentifyCharacter.o $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestIdentifyCharacter.o -Lbuild $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
	bin/TestIdentifyCharacter
	
TestGUI: build/TestGUI.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestGUI.o -Lbuild  $(VIEW_LIB_COMPILE) $(CONTROL_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@
	
TestCompile: build/TestCompile.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestCompile.o -Lbuild  $(VIEW_LIB_COMPILE) $(CONTROL_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@
	
#************************ TEST OF WHOLE SYSTEM WITHOUT GUI ************************		
TestSystem: build/TestSystem.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/TestSystem.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
	
#************************ TEST OF WHOLE SYSTEM WITHOUT GUI ************************

OCR: build/OCR.o $(VIEW_LIB_DEPEND) $(CONTROL_LIB_DEPEND) $(MODEL_LIB_DEPEND)
	$(info Linking $@)
	@$(CC) build/OCR.o -Lbuild $(CONTROL_LIB_COMPILE) $(VIEW_LIB_COMPILE) $(MODEL_LIB_COMPILE) $(GUI_LFLAGS) $(LDFLAGS) -o bin/$@ 
